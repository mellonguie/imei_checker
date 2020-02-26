# IMEI and IMEISV checking tool

It's a tool which enables to check the validity of IMEI and IMEISV. \
For more details what is IMEI and IMEISV, please take a look on that document : https://www.arib.or.jp/english/html/overview/doc/STD-T63V12_00/5_Appendix/Rel13/23/23003-d50.pdf

### Build :
```
git clone https://github.com/mellonguie/imei_imeisv_checking.git 
cd imei_imeisv_checking
make
```

### Usage :
```
./imei_imeisv_checking <my-imei-imeisv>
```

### Example :
```
./imei_imeisv_checking 354784054129987
IMEI/IMEISV: 354784054129987
TAC: 35478405
SNR: 412998
CD: 7
IMEI: 354784054129987 is valid.

./imei_imeisv_checking 3547840541299059
IMEI/IMEISV: 3547840541299059
TAC: 35478405
SNR: 412990
SVN: 59
IMEISV: 3547840541299059
```

### Notes :
**TAC** : Type Allocation Code (is 8 bytes long) \
**SNR** : Serial Number (is 6 bytes long) \
**CD**  : Check Digit (is 1 byte long) \
**SVN** : Software Version Number (is 2 bytes long)

*If you find any bugs, don't hesitate to create an issue. I will fix it.* \
*Have fun ! ;)*
