import styled from 'styled-components';
import { FC } from 'react';

const Container = styled.header`
  display: flex;
  align-items: center;
  justify-content: space-between;
  height: 60px;
  border-bottom: 1px solid ${({ theme }): string => theme.colors.red};
  padding: 0 20px;
`;

const GitHub = styled.a`
  text-decoration: none;
  cursor: pointer;

  &:link {
    color: ${({ theme }): string => theme.colors.tertiary};
  }

  &:visited {
    color: ${({ theme }): string => theme.colors.tertiary};
  }

  &:hover {
    color: ${({ theme }): string => theme.colors.tertiary};
  }

  &:active {
    color: ${({ theme }): string => theme.colors.tertiary};
  }
  &:after {
    content: 'GitHub';
  }
`;

const Header: FC = () => {
  return (
    <Container>
      <div>SIROCCO</div>
      <GitHub href="https://github.com/timbergus/sirocco" target="_blank" />
    </Container>
  );
};

export default Header;
