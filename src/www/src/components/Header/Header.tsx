import styled from "styled-components";
import { FC } from "react";

const Container = styled.header`
  display: flex;
  align-items: center;
  justify-content: space-between;
  height: 60px;
  border: 1px solid red;
  padding: 0 20px;
`;

const Header: FC = () => {
  return (
    <Container>
      <div>SIROCCO</div>
      <div>GitHub</div>
    </Container>
  );
};

export default Header;
