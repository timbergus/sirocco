#include "comms.h"

Comms::Comms()
{
  read_env_file("src/server/.env", env);
}

Comms::~Comms()
{
}

void Comms::set_public_path(std::string public_path)
{
  std::filesystem::path p(public_path);
  this->public_path = p.lexically_normal();
}

void Comms::create_socket()
{
#ifdef _WIN32
  WSADATA wsaData;
  WORD DllVersion = MAKEWORD(2, 2);

  if (WSAStartup(DllVersion, &wsaData) != 0)
  {
    std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
    exit(EXIT_FAILURE);
  }
#endif

  socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

#ifdef _WIN32
  if (socket_fd == INVALID_SOCKET)
  {
    std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
    WSACleanup();
    exit(EXIT_FAILURE);
  }
#else
  if (socket_fd == -1)
  {
    std::cerr << "Error at socket(): " << strerror(errno) << std::endl;
    exit(EXIT_FAILURE);
  }
#endif
}

void Comms::bind_socket(int port)
{
  this->port = port;

  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = INADDR_ANY;
  sockaddr.sin_port = htons(port);

  if (bind(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
  {
    std::cout << fmt::format("Failed to bind to port {}. Errno: {}\n", port, errno);
    exit(EXIT_FAILURE);
  }
}

void Comms::listen_connection()
{
  if (listen(socket_fd, 10) < 0)
  {
    std::cout << fmt::format("Failed to listen on socket. Errno: {}\n", errno);
    exit(EXIT_FAILURE);
  }

  std::cout << fmt::format("\nListening on http://localhost:{}\n", port);
}

void Comms::accept_connection()
{
  unsigned long addrlen = sizeof(sockaddr);

  connection = accept(socket_fd, (struct sockaddr *)&sockaddr, (socklen_t *)&addrlen);

  if (connection < 0)
  {
    std::cout << "Failed to grab connection." << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Comms::read_request()
{
  char received_request[1024];

#ifdef _WIN32
  int n = recv(connection, received_request, sizeof(received_request), 0);
#else
  int n = read(connection, received_request, sizeof(received_request));
#endif
  if (n < 0)
  {
    std::cout << "Failed reading the message." << std::endl;
    exit(EXIT_FAILURE);
  }

  request.parse_request(received_request);
}

void Comms::send_contents(std::string content, std::string extension, int status_code)
{
  response.set_status_code(status_code);
  response.set_content_type(extension);
  std::string msg = response.compose_response(content);
  send(connection, msg.c_str(), msg.size(), 0);
}

void Comms::send_file(std::string file_name)
{
  std::string path = fmt::format(
      "{}/{}/{}",
      env["ROOT_PATH"],
      public_path.string(),
      file_name.empty() ? "index.html" : file_name);

  std::filesystem::path file_path(path);

  std::string file = read_file(file_path.lexically_normal().string());

  send_contents(file, file_path.extension().string().substr(1));
}

void Comms::send_not_implemented()
{
  send_contents("<h1>501 Not implemented</h1>", "html", 501);
}

void Comms::send_server_error()
{
  send_contents("<h1>500 server error</h1>", "html", 500);
}

void Comms::close_connection()
{
#ifdef _WIN32
  closesocket(connection);
#else
  close(connection);
#endif
}

void Comms::close_socket()
{
#ifdef _WIN32
  closesocket(socket_fd);
  WSACleanup();
#else
  close(socket_fd);
#endif
}
