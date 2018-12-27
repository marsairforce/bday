// FLAGS.H
// TEMPLATE CLASS FOR A BIT MASKED FLAG STRUCTURE
// LAST MODIFIED 02/16/99 BY TRAVIS HEIN

#if !defined FLAGS
#define FLAGS
template <class T>
class flags
  {
  private:
    T flag_data;
  public:
    flags(T a = 0) {flag_data = a; }
    void SetFlag(T mask) { flag_data |= mask; }
    void ClrFlag(T mask) { flag_data &=~mask; }
    void TglFlag(T mask) { flag_data ^= mask; }
    T GetFlag(T mask) { return flag_data & mask;           }
    T IsFlag(T mask)  { return (flag_data & mask) ? 1 : 0; } // new experimental routine!
    void Load(T val)     { flag_data = val; }
    T Read() 	    { return flag_data; }
    void Reset() { flag_data = 0; }
  };
#endif

