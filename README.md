# from_chars-to_chars-conversion-test
How many digits we need for precise std::from_chars &lt;-> std::to_chars roundtrip.

STL implemented [from_chars](https://en.cppreference.com/w/cpp/utility/from_chars) and [to_chars](https://en.cppreference.com/w/cpp/utility/to_chars) in VC++ for C++17.

Win10 x64, r1909, VS2019, 16.5 preview 5.

Code in this repo tries to test all 2^32 float numbers by doing to_chars->from_chars roundtrip and comparing the result.

We skip NaNs and Infs.

First, we would like to check if this conversion is exact, with no loss of precision.

Second, we would like to check how many digits are required to make such roundtrip precise, in responce to discussion [here](https://www.johndcook.com/blog/2020/03/16/round-trip-radix-conversion/#comments).

9 digits, folks, John is right.

Checked 4278190080 floats, (one of the) longest one is -1.00000075e-36.
