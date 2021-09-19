import "./index.css";

import { StrictMode } from "react";
import { render } from "react-dom";

import App from "./app/App";

render(
  <StrictMode>
    <App />
  </StrictMode>,
  document.getElementById("root"),
);
