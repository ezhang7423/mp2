<template>
  <div>
    <!-- size -->
    <div>
      <div class="flow-root">
        <p class="float-left">Size</p>
        <p class="float-right">{{ size }}x{{ size }}</p>
      </div>
      <input
        v-model="size"
        type="range"
        max="18"
        min="5"
        class="range range-xs"
      />
    </div>

    <!-- color -->
    <div class="flex items-center pb-3" style="min-width: 150px">
      <p class="mr-5">I play as {{ white ? 'White' : 'Black' }}</p>
      <input
        v-model="white"
        type="radio"
        name="opt"
        class="radio"
        :disabled="false"
        @click="white = !white"
      />
    </div>

    <!-- show debug info -->
    <div class="flex items-center pb-3" style="min-width: 150px">
      <p class="mr-5">Show debug info</p>
      <input
        v-model="showDebug"
        type="checkbox"
        checked="checked"
        class="checkbox checkbox-accent"
      />
    </div>

    <div>
      <button class="btn-sm btn btn-outline">Back</button>
      <button class="btn-sm btn btn-outline">Next</button>
      <button class="btn-sm btn btn-outline">Resign</button>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      white: false,
      showDebug: true,
      size: 11,
    }
  },
}
</script>

<style>
</style>