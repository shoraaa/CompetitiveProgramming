//////////////////////////////////////////////////
// score with AMM2
// Author: Do Duc Dong



//                        id'problem here...

const           id                      ='XN';
                fi                      ='compar$r.inp';
                fo                      ='compar$r.out';
                max                     =3000;


var             path                    :string;
                f                       :text;
                err                     :longint;
                errMsg                  :array[1..100]of string;
                v           :array[1..max,1..20]of integer;
                d           :array[1..max]of integer;
                n,m,w       :integer;
                diem,dem    :integer;
                ds          :longint;
                snk         :longint;


procedure sort(p  :  integer);
var   i,j,coc  :    integer;
begin
     for i := 1 to m-1 do
         for j := i +1  to m do
             if v[p,i] > v[p,j] then
                begin
                     coc := v[p,i];
                     v[p,i] := v[p,j];
                     v[p,j] := coc;
                end;
end;

function ilhj(  i,j  :  integer)  :  boolean; { vt[i] >= vt[j] }
var p  :  integer;
begin
      ilhj := false;
     for p := 1 to m do
         if v[i,p] < v[j,p] then exit;
     ilhj := true;
end;

procedure readPath;
 begin
   // doc lay duong dan
   assign(f,fi); reset(f);
   read(f,path);
   close(f);
 end;

procedure readInput;
var i,j :longint;
 begin
   //doc du lieu
   //file input nam trong duong dan path
   assign(f,path+id+'.inp'); reset(f);
   readln(f,n,m,snk);
   for i:=1 to n do
     begin
        for j:=1 to m do read(f,v[i,j]);
        //sort(i);
     end;

   close(f);

 end;

procedure readOutput;
var i, x,y, tmp :longint;
 begin
   //doc dap an
   //file output nam trong duong dan path
   assign(f,path+id+'.out'); reset(f);

   read(f,ds);

   close(f);

 end;

procedure readHs;
var i,j,x,y :longint;
 begin
   err:=0;

   //doc lay ket qua hoc sinh
   assign(f,id+'.out'); reset(f);

   dem:=0;
   fillchar(d,sizeof(d),0);

   if (ds=-1) then begin
     readln(f,w);
     if w<>-1 then begin
        err:=4;
        errMsg[4]:='Ket luan sai';
        close(f);
        exit;
     end;
     close(f);
     exit;
   end;

   for i:=1 to snk do
     begin
       while not seekeoln(f) do
         begin
           read(f,j);inc(dem);
           if (j>n)and(j<1) then begin
                err:=5;
                errMsg[5]:='chi so hs khong dung';
                exit;
           end;

           if d[j]=0 then d[j]:=i
            else
              begin
                err:=1;
                errMsg[1]:='hs xuat hien >1 lan';
                exit;
              end;
         end;
       readln(f);
     end;
   close(f);

   if dem<>n then
     begin
       err:=2;
       errMsg[2]:='Khong du n thi sinh ';
       exit;
     end;

   for i:=1 to n-1 do
    for j:=i+1 to n do
      if (d[i]=d[j])and(ilhj(i,j) or ilhj(j,i)) then
        begin
          err:=3;
          errMsg[3]:='xung dot';
          exit;
        end;

 end;


procedure writeScore;
 begin
   assign(f,fo); rewrite(f);

   if err=0 then writeln(f,'DUNG')
   else begin
           writeln(f,'SAI');
           writeln(f,errMsg[err]);
        end;

   close(f);

 end;

BEGIN

   // doc duong dan
   readPath;

   //doc du lieu vao
   readInput;

   //doc dap an
   readOutput;

   //doc ket qua hoc sinh
   readHs;

   //ghi ket qua
   writeScore;
END.
