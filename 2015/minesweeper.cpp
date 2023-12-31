bool** cerintaB(int** a, int n, int m)
{
  int** tmp = new int*[n+2];
  for (int i = 0; i < n+2; i++)
  {
    tmp[i] = new int[m+2];
    for (int j = 0; j < m+2; j++)
      if (i >= 1 && i <= n && j >= 1 && j <= m)
        tmp[i][j] = a[i-1][j-1];
      else
        tmp[i][j] = 0;
  }
  bool** b = new bool*[n];
  int dx[] = {-1,-1,-1,1,1,1,0,0};
  int dy[] = {-1,0,1,-1,0,1,-1,1};
  for (int i = 1; i <= n; i++)
  {
    b[i-1] = new bool[m];
    for (int j = 1; j <= m; j++)
    {
      bool ok = 0;
      for (int d = 0; d < 8; d++)
      {
        int lin = dx[d] + i;
        int col = dy[d] + j;
        if (tmp[lin][col] == -1)
        {
          ok = 1;
          break;
        }
      }
      b[i-1][j-1] = ok;
    }
  }
  return b;
}
int** cerintaC(int**a, int n, int m, int l, int c)
{
  if (a[l][c] == -1)
    return a;
  int** b = new int*[n];
  for (int i = 0; i < n; i++)
  {
    b[i] = new int[m];
    for (int j = 0; j < m; j++)
      b[i][j] = -2;
  }
  int dx[] = {-1,-1,-1,1,1,1,0,0};
  int dy[] = {-1,0,1,-1,0,1,-1,1};
  bool** z = cerintaB(a, n, m);
  if (z[l][c] == 1)
  {
    int nr = 0;
    for (int d = 0; d < 8; d++)
    {
      int lin = dx[d] + l;
      int col = dy[d] + c;
      if (lin >= 0 && lin < n && col >= 0 && col < m
          && a[lin][col] == -1)
        nr++;
    }
    b[l][c] = nr;
    return b;
  }
  struct Punct { int x, y; } C[n*m];
  int inc = 0, sf = 0;
  C[inc] = {l, c};
  a[l][c] = 1;
  b[l][c] = 0;
  while (inc <= sf)
  {
    Punct p = C[inc++];
    for (int d = 0; d < 8; d++)
    {
      int lin = p.x + dx[d];
      int col = p.y + dy[d];
      if (lin >= 0 && lin < n && col >= 0 && col < m
          && z[lin][col] == 0 && a[lin][col] == 0)
      {
        a[lin][col] = a[p.x][p.y] + 1;
        b[lin][col] = 0;
        C[++sf] = {lin, col};
      }
    }
  }
  for (int i = 0; i <= sf; i++)
    for (int d = 0; d < 8; d++)
    {
      int lin = C[i].x + dx[d];
      int col = C[i].y + dy[d];
      if (lin >= 0 && lin < n && col >= 0 && col < m
          && a[lin][col] == 0)
      {
        int nr = 0;
        for (int k = 0; k < 8; k++)
        {
          int ii = lin + dx[k];
          int jj = col + dy[k];
          if (ii >= 0 && ii < n && jj >= 0 && jj < m
              && a[ii][jj] == -1)
            nr++;
        }
        b[lin][col] = nr;
      }
    }
  return b;
}

