import styled from "styled-components";
import { FC } from "react";

import Header from "../components/Header/Header";
import Footer from "../components/Footer/Footer";

const Container = styled.div`
  display: flex;
  flex-direction: column;
  height: 100vh;
`;

const Title = styled.div`
  color: var(--primary);
  text-transform: uppercase;
  font-size: 4em;
  font-weight: 100;
`;

const Contents = styled.div`
  flex: 1;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
`;

const App: FC = () => {
  return (
    <Container>
      <Header />
      <Contents>
        <Title>Hello Sirocco!</Title>
        <p>Welcome to the next gen C++ servers.</p>
      </Contents>
      <Footer />
    </Container>
  );
};

export default App;
