import { render } from '@testing-library/react';

import App from './Header';

describe('App component', () => {
  test('should render.', () => {
    const component = render(<App />);
    expect(component).not.toBeNull();
  });
});
