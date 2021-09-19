import { render } from "@testing-library/react";

import App from "./Footer";

describe("App component", () => {
  test("should render.", () => {
    const component = render(<App />);
    expect(component).not.toBeNull();
  });
});
