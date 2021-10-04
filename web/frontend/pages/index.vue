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
            :current-player="current_player"
            :condition="game_state.condition"
            :size="size"
            @switchCurrent="current_player = Number(!current_player)"
            @newSize="size = Number($event)"
            @changeCondition="changeCondition"
          />
        </div>

        <div
          style=""
          class="mt-8 bg-white overflow-hidden shadow sm:rounded-lg p-6 mx-3"
        >
          <Grid :state="game_state.state" @move="move" />
        </div>
      </div>
    </div>
    <Footer class="pb-5" />
  </div>
</template>

<script>
import { GameCondition, Player } from '~/utils/enums'
export default {
  data() {
    return {
      size: 11,
      nextMove: null,
      current_player: Player.Human,
      game_state: {
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
      this.game_state.state = Array(this.size).fill(Array(this.size).fill(null))
    },
  },
  methods: {
    move(rc) {
      if (this.game_state.condition !== GameCondition.InProgress) return
      // nextMove = $event
      const [r, c] = rc
      const newState = JSON.parse(JSON.stringify(this.game_state.state))
      newState[r][c] = 1
      this.$set(this.game_state, 'state', newState)
    },
    startGameLoop() {
      // while (game.not_finished()) {}
      // this.game_state.condition = GameCondition.Finished
    },
    changeCondition() {
      if (this.game_state.condition === GameCondition.InProgress) {
        this.game_state.condition = GameCondition.Finished
        // do some other stuff
      } else if (this.game_state.condition === GameCondition.NotStarted) {
        this.game_state.condition = GameCondition.InProgress
        this.startGameLoop()
      } else {
        // condition is finished
        this.game_state.condition = GameCondition.InProgress
        this.startGameLoop()
      }
    },
  },
}
</script>
