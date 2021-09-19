import styled from "styled-components";
import { FC } from "react";

const Container = styled.footer`
  display: flex;
  align-items: center;
  justify-content: flex-end;
  height: 60px;
  border: 1px solid red;
  padding: 0 20px;
`;

const Footer: FC = () => {
  return (
    <Container>
      <div>© Gustavo Muñoz, {new Date().getFullYear()}</div>
    </Container>
  );
};

export default Footer;
