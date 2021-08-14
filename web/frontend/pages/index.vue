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
          style="height: fit-content"
        >
          <h3 class="text-xl pb-5">Controls</h3>
          <Controls :size="size" @newSize="size = Number($event)" />
        </div>

        <div
          class="mt-8 bg-white overflow-hidden shadow sm:rounded-lg p-6 mx-3"
        >
          <Grid :size="size" />
        </div>
      </div>
    </div>
    <Footer class="pb-5" />
  </div>
</template>

<script>
export default {
  data() {
    return {
      size: 11,
    }
  },
}
</script>
