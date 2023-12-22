import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'

// https://vitejs.dev/config/
export default defineConfig({
  base: '/sirocco/',
  server: {
    port: 5432,
  },
  build: {
    outDir: '../../docs',
    emptyOutDir: true,
  },
  plugins: [react()],
})
