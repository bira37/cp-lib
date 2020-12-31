struct XorBasis {
#define BASIS_SIZE 60
  using BitArray = bitset<BASIS_SIZE>;

  vector<BitArray> basis;

  XorBasis() { basis.resize(BASIS_SIZE, BitArray(0)); }

  int get_msb(BitArray x) {
    for (int i = BASIS_SIZE - 1; i >= 0; i--) {
      if (x[i]) return i;
    }
    return -1;
  }

  bool add(BitArray x) {
    for (int i = BASIS_SIZE - 1; i >= 0; i--) {
      if (basis[i].none()) continue;
      if (get_msb(x) == i) {
        x ^= basis[i];
      }
    }
    if (x != 0) {
      basis[get_msb(x)] = x;
      return true;
    }
    return false;
  }

  bool has(BitArray x) {
    for (int i = BASIS_SIZE - 1; i >= 0; i--) {
      if (basis[i].none()) continue;
      if (get_msb(x) == i) {
        x ^= basis[i];
      }
    }
    return x.none();
  }

  BitArray to_bitarray(int x) { return BitArray(x); }

#undef BASIS_SIZE
};
