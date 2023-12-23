import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import { RecoilRoot } from 'recoil'
import { ThemeProvider } from 'styled-components'

import theme from './theme'
import { App } from './app/App'
import { GlobalStyle } from './components/GlobalStyle'

const container = document.getElementById('root')

const root = createRoot(container as HTMLElement)

root.render(
  <StrictMode>
    <ThemeProvider theme={theme}>
      <RecoilRoot>
        <GlobalStyle />
        <App />
      </RecoilRoot>
    </ThemeProvider>
  </StrictMode>,
)
