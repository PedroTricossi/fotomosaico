void** allocateMatrixMemory(int size, long int width, long int height){
  void** m;

  m = malloc(height * sizeof(void*));
  m[0] = malloc(height * width * size);
  for (int i=1; i < height; i++)
      m[i] = m[0] + i * width * size;

  return m;
}