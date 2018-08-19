kernel void vadd(global double* a, global double* b, global double* ans)
{
        int id = get_global_id(0);
        ans[id] = a[id] * b[id];

}

