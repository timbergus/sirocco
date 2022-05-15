import styled from 'styled-components'
import { ChangeEvent, FC } from 'react'

const Container = styled.div`
  display: flex;
  align-items: center;
  height: 1.5rem;
  gap: 1rem;
  width: 20rem;
  justify-content: space-between;

  div:first-child {
    width: 4rem;
    text-align: left;
    color: ${({ theme }) => theme.colors.primary};
  }

  input {
    flex: 1;
    cursor: pointer;
  }

  div:last-child {
    width: 2rem;
    text-align: right;
    color: ${({ theme }) => theme.colors.yellow};
  }
`

type Props = {
  label: string
  step: number
  max: number
  value: number
  onChange: (value: number) => void
}

const Control: FC<Props> = ({ label, step, max, value, onChange }) => {
  return (
    <Container>
      <div>{label}</div>
      <input
        type="range"
        min={0}
        max={max}
        step={step}
        value={value}
        onChange={(event: ChangeEvent<HTMLInputElement>) =>
          onChange(Number(event.target.value))
        }
      />
      <div>{value}</div>
    </Container>
  )
}

export default Control
