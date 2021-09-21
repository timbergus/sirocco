import styled from 'styled-components';
import { FC, useState } from 'react';
import { useRecoilValue } from 'recoil';
import { debugState } from '../../atoms';

import Control from './Control';

const Controllers = styled.div`
  padding: 1rem 0;
`;

const Logo: FC = () => {
  const isDebug = useRecoilValue(debugState);

  const [offsetX, setOffsetX] = useState(15);
  const [offsetY, setOffsetY] = useState(25);
  const [sizeX, setSizeX] = useState(170);
  const [sizeY, setSizeY] = useState(150);
  const [guideX1, setGuideX1] = useState(2);
  const [guideX2, setGuideX2] = useState(5);
  const [guideX3, setGuideX3] = useState(8);
  const [guideY1, setGuideY1] = useState(4);
  const [guideY2, setGuideY2] = useState(5);
  const [guideY3, setGuideY3] = useState(6);

  const guidesX = [
    offsetX + 0,
    offsetX + (sizeX * guideX1) / 10,
    offsetX + (sizeX * guideX2) / 10,
    offsetX + (sizeX * guideX3) / 10,
    offsetX + sizeX,
  ];
  const guidesY = [
    offsetY + 0,
    offsetY + (sizeY * guideY1) / 10,
    offsetY + (sizeY * guideY2) / 10,
    offsetY + (sizeY * guideY3) / 10,
    offsetY + sizeY,
  ];

  const points = [
    [guidesX[1], guidesY[0]],
    [guidesX[3], guidesY[0]],
    [guidesX[4], guidesY[1]],
    [guidesX[2], guidesY[1]],
    [guidesX[4], guidesY[2]],
    [guidesX[4], guidesY[3]],
    [guidesX[3], guidesY[4]],
    [guidesX[1], guidesY[4]],
    [guidesX[0], guidesY[3]],
    [guidesX[2], guidesY[3]],
    [guidesX[0], guidesY[2]],
    [guidesX[0], guidesY[1]],
  ];

  return (
    <>
      <svg xmlns="http://www.w3.org/2000/svg" width={200} height={200}>
        <circle cx="100" cy="100" r="100" fill="#903030" />
        <polygon points={points.flat().join(', ')} fill="#d1c131" />
      </svg>
      {isDebug && (
        <Controllers>
          <Control
            label="Offset X"
            step={5}
            max={100}
            value={offsetX}
            onChange={setOffsetX}
          />
          <Control
            label="Offset Y"
            step={5}
            max={100}
            value={offsetY}
            onChange={setOffsetY}
          />
          <Control
            label="Size X"
            step={5}
            max={200}
            value={sizeX}
            onChange={setSizeX}
          />
          <Control
            label="Size Y"
            step={5}
            max={200}
            value={sizeY}
            onChange={setSizeY}
          />
          <Control
            label="Guide X1"
            step={1}
            max={10}
            value={guideX1}
            onChange={setGuideX1}
          />
          <Control
            label="Guide X2"
            step={1}
            max={10}
            value={guideX2}
            onChange={setGuideX2}
          />
          <Control
            label="Guide X3"
            step={1}
            max={10}
            value={guideX3}
            onChange={setGuideX3}
          />
          <Control
            label="Guide Y1"
            step={1}
            max={10}
            value={guideY1}
            onChange={setGuideY1}
          />
          <Control
            label="Guide Y2"
            step={1}
            max={10}
            value={guideY2}
            onChange={setGuideY2}
          />
          <Control
            label="Guide Y3"
            step={1}
            max={10}
            value={guideY3}
            onChange={setGuideY3}
          />
        </Controllers>
      )}
    </>
  );
};

export default Logo;
