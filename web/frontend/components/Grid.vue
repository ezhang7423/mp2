<template>
  <table>
    <tbody class="square-cells">
      <tr>
        <th></th>
        <th v-for="i of rows" :key="`1-${i}`">{{ i }}</th>
        <th></th>
      </tr>
      <tr v-for="i of rows" :key="i" :data-row="i">
        <th>{{ i }}</th>
        <td v-for="j of rows" :key="`${i}-${j}`">&nbsp;</td>
        <th>{{ i }}</th>
      </tr>

      <tr>
        <th></th>
        <th v-for="i of rows" :key="`end-${i}`">{{ i }}</th>
        <th></th>
      </tr>
    </tbody>
  </table>
</template>

<script>
export default {
  props: {
    size: { type: Number, required: true },
  },
  computed: {
    rows() {
      return [...Array(this.size).keys()]
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
  background-image: url(/x64.png);
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