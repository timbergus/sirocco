import { RecoilRoot } from 'recoil'
import { render, screen } from '@testing-library/react'
import { ThemeProvider } from 'styled-components'

import theme from '../../theme'

import App from '../App'

describe('App component', () => {
  test('should render.', () => {
    render(
      <ThemeProvider theme={theme}>
        <RecoilRoot>
          <App />
        </RecoilRoot>
      </ThemeProvider>,
    )
    const text = screen.getByText('Hello Sirocco!')
    expect(text).toBeInTheDocument()
  })
})
