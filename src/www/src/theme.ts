import { DefaultTheme } from 'styled-components'

const sizeBase = 16

const theme: DefaultTheme = {
  colors: {
    primary: '#6ee666',
    secondary: '#353535',
    tertiary: '#d8d8d8',
    red: '#903030',
    yellow: '#d1c131',
  },
  fontSizes: {
    xs: `${sizeBase / 2}px`,
    sm: `${sizeBase / 1.5}px`,
    md: `${sizeBase}px`,
    lg: `${sizeBase * 1.5}px`,
    xl: `${sizeBase * 2}px`,
    xxl: `${sizeBase * 3}px`,
  },
  spacing: (value: number): number => sizeBase * value,
}

export default theme
