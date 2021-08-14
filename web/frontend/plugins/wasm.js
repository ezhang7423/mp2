export default async ({ app }, inject) => {
  // Inject $hello(msg) in Vue, context and store.
  const wasm = await import('~/wasm/core_bg.js').catch(console.error)

  inject('wasm', wasm)
}
