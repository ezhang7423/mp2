<template>
  <div>
    <!-- size -->
    <div>
      <div class="flow-root">
        <p class="float-left">Size</p>
        <p class="float-right">{{ size }}x{{ size }}</p>
      </div>
      <input
        :value="size"
        :disabled="condition === GameCondition.InProgress"
        type="range"
        max="18"
        min="5"
        class="range range-xs"
        @input="$emit('newSize', $event.target.value)"
      />
    </div>

    <!-- color -->
    <div class="flex items-center py-3" style="min-width: 150px">
      <p class="mr-5">I play as {{ currentPlayer ? 'White' : 'Black' }}</p>
      <input
        :checked="!currentPlayer"
        type="radio"
        name="opt"
        class="radio"
        :disabled="condition === GameCondition.InProgress"
        @click="$emit('switchCurrent')"
      />
    </div>

    <!-- show debug info -->
    <div class="flex items-center pb-3" style="min-width: 150px">
      <p class="mr-5">Show debug info</p>
      <input
        v-model="showDebug"
        :disabled="condition === GameCondition.InProgress"
        type="checkbox"
        checked="checked"
        class="checkbox checkbox-accent"
      />
    </div>

    <div>
      <!-- <button class="btn-sm btn btn-outline">Back</button>
      <button class="btn-sm btn btn-outline">Next</button> -->
      <button class="btn-sm btn btn-outline" @click="changeCondition">
        {{ condition === GameCondition.InProgress ? 'Resign' : 'Start' }}
      </button>
    </div>
  </div>
</template>

<script>
import { GameCondition } from '~/utils/enums'
export default {
  props: {
    size: {
      type: Number,
      required: true,
    },
    condition: {
      type: Number,
      required: true,
    },
    currentPlayer: {
      type: Number,
      required: true,
    },
  },
  data() {
    return {
      GameCondition,
      showDebug: true,
    }
  },

  methods: {
    changeCondition() {
      this.$emit('changeCondition')
    },
  },
}
</script>

<style>
</style>