import styled from 'styled-components'

import { Logo } from '../components/Logo'
import { Header } from '../components/Header'
import { Footer } from '../components/Footer'

const Container = styled.div`
  display: flex;
  flex-direction: column;
  height: 100vh;
`

const Title = styled.div`
  color: ${({ theme }): string => theme.colors.primary};
  text-transform: uppercase;
  font-size: 4em;
  font-weight: 100;
`

const Contents = styled.div`
  flex: 1;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
`

export const App = () => (
  <Container>
    <Header />
    <Contents>
      <Logo />
      <Title>Hello Sirocco!</Title>
      <p>Welcome to the next-gen C++ server</p>
    </Contents>
    <Footer />
  </Container>
)
