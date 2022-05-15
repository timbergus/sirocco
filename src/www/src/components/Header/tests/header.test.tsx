import { RecoilRoot } from 'recoil'
import { render, screen } from '@testing-library/react'
import { ThemeProvider } from 'styled-components'

import theme from '../../../theme'

import Header from '../Header'

describe('Header component', () => {
  test('should render.', () => {
    render(
      <ThemeProvider theme={theme}>
        <RecoilRoot>
          <Header />
        </RecoilRoot>
      </ThemeProvider>,
    )
    const text = screen.getByText('SIROCCO')
    expect(text).toBeInTheDocument()
  })
})
