<template>
  <div
    class="
      relative
      flex flex-col
      items-top
      align-center
      min-h-screen
      bg-gray-100
      sm:pt-0
    "
  >
    <div class="flex-grow max-w-screen-2xl w-full sm:px-6 lg:px-8">
      <div class="flex">
        <div
          class="mt-8 bg-white overflow-hidden shadow sm:rounded-lg p-6 mx-3"
          style="height: fit-content; min-width: 250px"
        >
          <h3 class="text-xl pb-5">Controls</h3>
          <Controls
            :current-player="gS.currentPlayer"
            :condition="gS.condition"
            :size="size"
            @switchCurrent="gS.currentPlayer = Number(!gS.currentPlayer)"
            @newSize="size = Number($event)"
            @changeCondition="changeCondition"
          />
        </div>

        <div
          style=""
          class="mt-8 bg-white overflow-hidden shadow sm:rounded-lg p-6 mx-3"
        >
          <Grid :state="gS.state" @move="cacheNextMove" />
        </div>
      </div>
    </div>
    <Footer class="pb-5" />
  </div>
</template>

<script>
import { GameCondition, Player, Color } from '~/utils/enums'
export default {
  data() {
    return {
      size: 11,
      nextMove: null,
      gameLoop: null,
      gS: {
        // gamestate
        currentColor: Color.White,
        currentPlayer: Player.Human,
        condition: GameCondition.NotStarted,
        state: [
          [null, null, null, null, null, null, null, null, null, null, null],
          [null, null, null, null, null, null, null, null, null, null, null],
          [null, null, null, null, null, null, null, null, null, null, null],
          [null, null, null, null, null, null, null, null, null, null, null],
          [null, null, null, null, null, null, null, null, null, null, null],
          [null, null, null, null, null, null, null, null, null, null, null],
          [null, null, null, null, null, null, null, null, null, null, null],
          [null, null, null, null, null, null, null, null, null, null, null],
          [null, null, null, null, null, null, null, null, null, null, null],
          [null, null, null, null, null, null, null, null, null, null, null],
          [null, null, null, null, null, null, null, null, null, null, null],
        ],
      },
    }
  },
  watch: {
    size() {
      this.gS.state = Array(this.size).fill(Array(this.size).fill(null))
    },
  },
  mounted() {
    this.startGameLoop()
  },
  methods: {
    cacheNextMove(rc) {
      this.nextMove = rc
    },
    move(rc) {
      if (this.gS.condition !== GameCondition.InProgress || rc === null) return

      const [r, c] = rc
      if (this.gS.state[r][c] !== null) return

      const newState = JSON.parse(JSON.stringify(this.gS.state))
      newState[r][c] = this.gS.currentColor
      this.gS.currentColor = Number(!this.gS.currentColor)
      this.$set(this.gS, 'state', newState)
    },
    startGameLoop() {
      this.gS.condition = GameCondition.InProgress
      this.gS.state = Array(this.size).fill(Array(this.size).fill(null))
      function finished(gameState) {
        return false
      }
      this.gameLoop = setInterval(() => {
        if (finished(this.gS)) {
          clearInterval(this.gameLoop)
          this.gS.condition = GameCondition.Finished
          return
        }
        if (this.gS.currentPlayer === Player.Robot) {
          this.move(this.nextMove)
        } else {
          this.move(this.nextMove)
        }
        this.nextMove = null
      }, 50)
    },
    changeCondition() {
      if (this.gS.condition === GameCondition.InProgress) {
        this.gS.condition = GameCondition.Finished
        // do some other stuff
      } else if (this.gS.condition === GameCondition.NotStarted) {
        this.startGameLoop()
      } else {
        // condition is finished
        this.startGameLoop()
      }
    },
  },
}
</script>
