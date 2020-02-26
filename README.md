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
IMEI: 354784054129987 is valid.
```

### Notes :
**TAC** : Type Allocation Code \
**SNR** : Serial Number \
**CD**  : Check Digit

*If you find any bugs, don't hesitate to create an issue. I will fix it.* \
*Have fun ! ;)*
