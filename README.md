# Concise

C++ implementation of CONCISE (COmpressed 'N' Composable Integer SEt) and WAH compressed bitsets.
The implementation is loosely based on Colantonio's original Java code.

Pre-requisite: gcc-like compiler (with C++11 support).

Usage :

```bash
make
./unit
```
## Other libraries
- See CRoaring https://github.com/RoaringBitmap/CRoaring
- See EWAHBoolArray https://github.com/lemire/EWAHBoolArray
- Git itself uses compressed bitsets https://github.com/git/git/tree/master/ewah

## Warning

Though this implementation is made freely available under the Apache License 2.0, WAH
was patented by its authors  and Concise is a derivative of WAH. I (Daniel Lemire) cannot garantee that this is
code can be safely used in commercial projects. Consult a lawyer.
