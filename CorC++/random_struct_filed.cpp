#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <iostream>


constexpr auto seed()
{
  std::uint64_t shifted = 0;

  for( const auto c : __TIME__ )
  {
    shifted <<= 8;
    shifted |= c;
  }

  return shifted;
}

struct PCG
{
  struct pcg32_random_t { std::uint64_t state=0;  std::uint64_t inc=seed(); };
  pcg32_random_t rng;
  typedef std::uint32_t result_type;

  constexpr result_type operator()()
  {
    return pcg32_random_r();
  }

  static result_type constexpr min()
  {
    return std::numeric_limits<result_type>::min();
  }

  static result_type constexpr max()
  {
    return std::numeric_limits<result_type>::min();
  }

  private:
  constexpr std::uint32_t pcg32_random_r()
  {
    std::uint64_t oldstate = rng.state;
    // Advance internal state
    rng.state = oldstate * 6364136223846793005ULL + (rng.inc|1);
    // Calculate output function (XSH RR), uses old state for max ILP
    std::uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    std::uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
  }

};

constexpr auto get_random(int count)
{
  PCG pcg;
  while(count > 0){
    pcg();
    --count;
  }
  
  return pcg();
}

constexpr int N = get_random(10) % 16;
struct obf{
    int pad[N];
    int a;
    int pad2[N+1];
    int c;
    int pad3[N+2];
    int d;
    int pad4[N+3];
};

int main()
{
  printf("%d\n",N);
  printf("%d\n",offsetof(obf, a));
  printf("%d\n",offsetof(obf, c));
  printf("%d\n",offsetof(obf, d));
  return 0;
}
