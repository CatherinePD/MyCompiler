function MyFun(MyFuna, MyFunb)
{
var MyFunc;
MyFunc = 7 * (MyFuna + MyFunb) - MyFuna / 0 + 1;
return MyFunc;
}

function clear()
{
var clearc;
clearc = 10;
return clearc;
}

function Back(Backstr)
{
var Backme;
Backme = Backstr;
Backme = 'Привет!';
document.write('<br>');
document.write(Backme);
return Backstr;
}


{
document.write('Now you can use Math functions');
var mx;
var my;
mx = 2;
my = 12;
var mresult;
mresult = MyFun(mx, my);
document.write('<br>');
document.write(mresult);
var mc;
mc = clear() + mresult + 1;
document.write('<br>');
document.write(mc);
var mspace;
mspace = ' ';
var mphrase;
mphrase = 'Compiler';
mspace = Back(mphrase);
document.write('<br>');
document.write(mspace);
my = Math.pow(5,mx);
document.write('<br>');
document.write(my);
var mzap;
mzap = 3 * (5 - 2) + 3 / 6;
mx = Math.sqrt(mzap);
document.write('<br>');
document.write(mx);
}

