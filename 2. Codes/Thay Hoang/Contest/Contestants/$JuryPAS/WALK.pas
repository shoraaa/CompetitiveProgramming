{$MODE OBJFPC}
program DoubleTours;
const
  InputFile  = 'WALK.INP';
  OutputFile = 'WALK.OUT';
  maxN = 100000;
  maxM = 100000;
  maxC = 2000000000;
  maxD = maxN * maxC;
type
  TEdge = record
    x, y: Integer;
    w: Integer;
    selected: Boolean;
  end;
  THeap = record
    nItems: Integer;
    items: array[1..maxN] of Integer;
    pos: array[1..maxN] of Integer;
  end;
  TTrace = array[1..maxN] of Integer;
var
  e: array[-maxM..maxM] of TEdge;
  link: array[-maxM..maxM] of Integer;
  head: array[1..maxN] of Integer;
  d: array[1..maxN] of Int64;
  trace: array[1..maxN] of Integer;
  price: array[1..maxN] of Int64;
  heap: THeap;
  n, m: Integer;
  d1, d2, res: Int64;
  p, q: array[1..maxN] of Integer;
  np, nq: Integer;

procedure Enter;
var
  f: TextFile;
  i, j, u, v: Integer;
begin
  AssignFile(f, InputFile); Reset(f);
  try
    ReadLn(f, n, m);
    for i := 1 to m do
      begin
        with e[i] do ReadLn(f, x, y, w);
        j := -i;
        e[j].x := e[i].y; e[j].y := e[i].x; e[j].w := e[i].w;
      end;
  finally
    CloseFile(f);
  end;
end;

procedure BuildIncidentLists;
var
  i: Integer;
begin
  FillDWord(head[1], n, 0);
  for i := -m to m do
    if i <> 0 then
      with e[i] do
        begin
          link[i] := head[x];
          head[x] := i;
        end;
end;

procedure Init;
var
  i: Integer;
begin
  FillChar(price[1], n * SizeOf(price[1]), 0);
  for i := -m to m do
    e[i].selected := False;
end;

function wp(const e: TEdge): Int64;
begin
  with e do
    Result := w + price[x] - price[y];
end;

procedure DijkstraInit;
var
  i: Integer;
begin
  for i := 1 to n do d[i] := maxD + 1;
  d[1] := 0;
  FillDWord(heap.pos[1], n, 0);
  heap.nItems := 1;
  heap.items[1] := 1;
end;

function Extract: Integer;
var
  p, c: Integer;
  v: Integer;
begin
  with Heap do
    begin
      Result := items[1];
      v := items[nItems];
      Dec(nItems);
      p := 1;
      repeat
        c := p * 2;
        if (c < nItems) and (d[items[c + 1]] < d[items[c]]) then Inc(c);
        if (c > nItems) or (d[items[c]] >= d[v]) then Break;
        items[p] := items[c];
        pos[items[p]] := p;
        p := c;
      until False;
      items[p] := v;
      pos[v] := p;
    end;
end;

function Update(v: Integer; dv: Int64): Boolean;
var
  p, c: Integer;
begin
  Result := d[v] > dv;
  if not Result then Exit;
  d[v] := dv;
  with Heap do
    begin
      c := pos[v];
      if c = 0 then
        begin
          Inc(nItems); c := nItems;
        end;
      repeat
        p := c div 2;
        if (p = 0) or (d[items[p]] <= d[v]) then Break;
        items[c] := items[p];
        pos[items[c]] := c;
        c := p;
      until False;
      items[c] := v;
      pos[v] := c;
    end;
end;

function Dijkstra: Boolean;
var
  u, v, i: Integer;
begin
  DijkstraInit;
  repeat
    u := Extract;
    if u = n then Exit(True);
    i := head[u];
    while i <> 0 do
      begin
        v := e[i].y;
        if not e[i].selected and Update(v, d[u] + wp(e[i])) then
          trace[v] := i;
        i := link[i];
      end;
  until heap.nItems = 0;
  Result := False;
end;

procedure AdjustPotentials;
var
  u, v, i: Integer;
begin
  for v := 1 to n do
    if d[v] < d[n] then
      Dec(price[v], d[n] - d[v]);
  v := n;
  repeat
    i := trace[v];
    e[i].selected := True;
    e[-i].w := -e[i].w;
    v := e[i].x;
  until v = 1;
end;

procedure RemoveEdges;
var
  i: Integer;
begin
  for i := 1 to m do
    if e[i].selected and e[-i].selected then
      begin
        e[i].selected := False;
        e[-i].selected := False;
      end;
end;

function Solve: Int64;
var
  u: Integer;
  i: Integer;
begin
  if not Dijkstra then Exit(-1);
  AdjustPotentials;
  d1 := price[n] - price[1];
  if not Dijkstra then Exit(-1);
  AdjustPotentials;
  d2 := price[n] - price[1];
  Result := d1 + d2;
  RemoveEdges;
  np := 0;
  u := 1;
  repeat
    Inc(np);
    p[np] := u;
    i := head[u];
    while not e[i].selected do i := link[i];
    u := e[i].y;
    e[i].selected := False;
  until u = n;
  nq := 0;
  u := 1;
  repeat
    Inc(nq);
    q[nq] := u;
    i := head[u];
    while not e[i].selected do i := link[i];
    u := e[i].y;
    e[i].selected := False;
  until u = n;
end;

procedure PrintResult;
var
  f: TextFile;
  k: Integer;
begin
  AssignFile(f, OutputFile); Rewrite(f);
  try
    WriteLn(f, Res);
    if Res <> -1 then
      begin
        for k := 1 to np do Write(f, p[k], ' ');
        Write(f, n);
        for k := nq downto 1 do Write(f, ' ', q[k]);
      end;
  finally
    CloseFile(f);
  end;
end;

begin
  Enter;
  BuildIncidentLists;
  Init;
  res := Solve;
  PrintResult;
end.
5 7 1 5
1 2 3
1 4 8
2 3 5
2 4 4
3 5 5
4 3 8
4 5 3
