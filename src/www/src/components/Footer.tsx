import styled from 'styled-components'
import { useRecoilState } from 'recoil'

import { debugState } from '../atoms'

const Container = styled.footer`
  display: flex;
  align-items: center;
  justify-content: space-between;
  height: 60px;
  border-top: 1px solid ${({ theme }): string => theme.colors.red};
  padding: 0 20px;
`

type DebugProps = {
  $isDebug: boolean
}

const Debug = styled.div<DebugProps>`
  color: ${({ theme, $isDebug }): string =>
    $isDebug ? theme.colors.primary : 'inherit'};
  cursor: pointer;
  user-select: none;
`

export const Footer = () => {
  const [isDebug, setIsDebug] = useRecoilState(debugState)

  const handleClick = () => {
    setIsDebug((state) => !state)
  }

  return (
    <Container>
      <Debug $isDebug={isDebug} onClick={handleClick}>
        Debug Mode
      </Debug>
      <div>© Gustavo Muñoz, {new Date().getFullYear()}</div>
    </Container>
  )
}
