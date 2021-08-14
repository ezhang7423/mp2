<template>
  <div
    class="
      relative
      flex
      items-top
      justify-center
      min-h-screen
      bg-gray-100
      sm:pt-0
    "
  >
    <div class="max-w-screen-2xl sm:px-6 lg:px-8">
      <div class="flex">
        <div
          class="mt-8 bg-white overflow-hidden shadow sm:rounded-lg p-6 mx-3"
        >
          <h2 class="text-2xl leading-7 font-semibold">Play against Madam</h2>
          <Grid />
        </div>
        <div
          class="mt-8 bg-white overflow-hidden shadow sm:rounded-lg p-6 mx-3"
        >
          <h3 class="text-xl pb-5">Controls</h3>
          <Controls />
        </div>
      </div>
      <Footer />
    </div>
  </div>
</template>

<script>
export default {}
</script>
