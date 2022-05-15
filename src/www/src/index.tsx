import { StrictMode } from 'react';
import { createRoot } from 'react-dom/client';
import { RecoilRoot } from 'recoil';
import { createGlobalStyle, ThemeProvider } from 'styled-components';

import App from './app/App';
import theme from './theme';

const GlobalStyle = createGlobalStyle`
  body {
    margin: 0;
    padding: 0;
    font-family: 'Roboto', sans-serif;
    -webkit-font-smoothing: antialiased;
    -moz-osx-font-smoothing: grayscale;
    color: ${({ theme }: { theme: any }): string => theme.colors.tertiary};
    background-color: ${({ theme }: { theme: any }): string =>
      theme.colors.secondary};
  }

  * {
    box-sizing: border-box;
  }
`;

const container = document.getElementById('root');

const root = createRoot(container as HTMLElement);

root.render(
  <StrictMode>
    <ThemeProvider theme={theme}>
      <RecoilRoot>
        <GlobalStyle />
        <App />
      </RecoilRoot>
    </ThemeProvider>
  </StrictMode>,
);
