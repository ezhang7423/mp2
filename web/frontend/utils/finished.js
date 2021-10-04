function finished(gameState) {
  const size = gameState.length

  // check with a sliding window from left to right, top to bottom
  for (let i = 0; i < size; i++) {
    for (let j = 0; j < size - 4; j++) {
      if (gameState[i][j] !== null && finishedHelper(gameState, i, j, true)) {
        return true
      }
    }
  }

  // top to bottom, left to right
  for (let j = 0; j < size; j++) {
    for (let i = 0; i < size - 4; i++) {
      if (gameState[i][j] !== null && finishedHelper(gameState, i, j, false)) {
        return true
      }
    }
  }

  // left diagonal from left to right
  if (finishedHelperDiag(gameState, true)) {
    return true
  }
  if (finishedHelperDiag(gameState, false)) {
    return true
  }

  return false
}

function finishedHelper(gameState, i, j, horizontal) {
  const firstColor = gameState[i][j]
  let finished = true
  for (let delta = 0; delta < 5; delta++) {
    // stop if there is any gap in the window
    const testColor = horizontal
      ? gameState[i][j + delta]
      : gameState[i + delta][j]

    if (testColor !== firstColor) {
      finished = false
      break
    }
  }
  return finished
}

function finishedHelperDiag(gameState, left) {
  const sz = gameState.length
  const iterSz = sz - 4

  for (let diag = iterSz - 1; diag > -iterSz; diag--) {
    for (let diagIdx = 0; diagIdx < sz - Math.abs(diag) - 4; diagIdx++) {
      let i = Math.max(diag, 0) + diagIdx
      const j = i - diag
      i = left ? i : sz - i - 1

      let finished = true
      const firstColor = gameState[i][j]
      if (firstColor === null) continue

      for (let delta = 0; delta < 5; delta++) {
        const testColor = left
          ? gameState[i + delta][j + delta]
          : gameState[i - delta][j + delta]
        if (testColor !== firstColor) {
          finished = false
          break
        }
      }
      if (finished) {
        return true
      }
    }
  }
  return false
}

export default finished
