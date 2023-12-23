import styled from 'styled-components'
import { ChangeEvent } from 'react'

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

type ControlProps = {
  label: string
  step: number
  max: number
  value: number
  onChange: (value: number) => void
}

export const Control = ({
  label,
  step,
  max,
  value,
  onChange,
}: ControlProps) => (
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
