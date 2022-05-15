import { RecoilRoot } from 'recoil'
import { render, screen } from '@testing-library/react'
import { ThemeProvider } from 'styled-components'

import theme from '../../../theme'

import Footer from '../Footer'

describe('Footer component', () => {
  test('should render.', () => {
    render(
      <ThemeProvider theme={theme}>
        <RecoilRoot>
          <Footer />
        </RecoilRoot>
      </ThemeProvider>,
    )
    const text = screen.getByText('Debug Mode')
    expect(text).toBeInTheDocument()
  })
})
