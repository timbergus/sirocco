import { createGlobalStyle } from 'styled-components'

import theme from '../theme'

export const GlobalStyle = createGlobalStyle<Partial<typeof theme>>`
  body {
    margin: 0;
    padding: 0;
    font-family: 'Roboto', sans-serif;
    -webkit-font-smoothing: antialiased;
    -moz-osx-font-smoothing: grayscale;
    color: ${({ theme }): string => theme.colors.tertiary};
    background-color: ${({ theme }): string => theme.colors.secondary};
  }

  * {
    box-sizing: border-box;
  }
`
