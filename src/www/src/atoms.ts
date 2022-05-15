import { atom } from 'recoil';

export const debugState = atom<boolean>({
  key: 'debugState',
  default: false,
});
