<!-- eslint-disable -->
<template>
  <table>
    <tbody class="square-cells">
      <tr>
        <th></th>
        <th v-for="(row, i) of state" :key="`1-${i}`">{{ i }}</th>
        <th></th>
      </tr>
      <tr v-for="(row, i) of state" :key="i" :data-row="i">
        <th>{{ i }}</th>
        <td
          @click="move(i, j)"
          v-for="(col, j) of state[i]"
          :style="{
            'background-image': bgImg(i, j),
          }"
          :key="`${i}-${j}`"
        >
          &nbsp;
        </td>
        <th>{{ i }}</th>
      </tr>
      <tr>
        <th></th>
        <th v-for="(row, i) of state" :key="`end-${i}`">{{ i }}</th>
        <th></th>
      </tr>
    </tbody>
  </table>
</template>

<script>
import { Color } from '~/utils/enums'
export default {
  props: {
    state: { type: Array, required: true },
  },
  methods: {
    bgImg(row, column) {
      if (this.state[row][column] === null) {
        return ''
      }
      if (this.state[row][column] === Color.Black) {
        return 'url(/game/x64b.png)'
      } else {
        return 'url(/game/x64w.png)'
      }
    },
    move(row, column) {
      this.$emit('move', [row, column])
    },
  },
}
</script>

<style scoped>
.square-cells * {
  width: 32px;
  min-width: 32px;
  height: 32px;
  min-height: 32px;
  text-align: center;
  vertical-align: middle;
  user-select: none;
  cursor: pointer;
}

td {
  background-size: 96px, 96px;
  background-repeat: repeat;
  background-position: 64px 64px;
  background-image: url(/game/x64.png);
}

td:nth-child(2) {
  background-position-x: 0;
}
td:nth-last-child(2) {
  background-position-x: 128px;
}
tr:nth-child(2) > td {
  background-position-y: 0;
}
tr:nth-last-child(2) > td {
  background-position-y: 128px;
}
th {
  font-weight: normal;
}
</style>