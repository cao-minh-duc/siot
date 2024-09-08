'use client';

import * as React from 'react';
import moment from 'moment';
import {
  ColumnDef,
  ColumnFiltersState,
  SortingState,
  VisibilityState,
  flexRender,
  getCoreRowModel,
  getFilteredRowModel,
  getPaginationRowModel,
  getSortedRowModel,
  useReactTable,
} from '@tanstack/react-table';
import { ArrowUpDown, ChevronDown, MoreHorizontal } from 'lucide-react';
import Image from 'next/image';

import { Button } from '@/components/ui/button';
import { Checkbox } from '@/components/ui/checkbox';
import {
  DropdownMenu,
  DropdownMenuCheckboxItem,
  DropdownMenuContent,
  DropdownMenuItem,
  DropdownMenuLabel,
  DropdownMenuSeparator,
  DropdownMenuTrigger,
} from '@/components/ui/dropdown-menu';
import { Input } from '@/components/ui/input';
import {
  Table,
  TableBody,
  TableCell,
  TableHead,
  TableHeader,
  TableRow,
} from '@/components/ui/table';

const data1: SensorData[] = [
  {
    activity_id: '1',
    activity_type: 'PUBLISH',
    created_at: '2024-04-01T11:00:00Z',
    value: 40.1,
  },
  {
    activity_id: '2',
    activity_type: 'ENABLE',
    created_at: '2024-04-02T11:01:00Z',
    value: 39.1,
  },
  {
    activity_id: '3',
    activity_type: 'DISABLE',
    created_at: '2024-04-03T11:02:00Z',
    value: 38.1,
  },
  {
    activity_id: '4',
    activity_type: 'PUBLISH',
    created_at: '2024-04-04T11:03:00Z',
    value: 37.1,
  },
  {
    activity_id: '5',
    activity_type: 'PUBLISH',
    created_at: '2024-04-05T11:04:00Z',
    value: 41.1,
  },
  {
    activity_id: '6',
    activity_type: 'DISABLE',
    created_at: '2024-04-06T11:05:00Z',
    value: 42.1,
  },
  {
    activity_id: '7',
    activity_type: 'ENABLE',
    created_at: '2024-04-07T11:06:00Z',
    value: 35.1,
  },
  {
    activity_id: '8',
    activity_type: 'PUBLISH',
    created_at: '2024-04-08T11:07:00Z',
    value: 30.1,
  },
  {
    activity_id: '9',
    activity_type: 'PUBLISH',
    created_at: '2024-04-08T11:08:00Z',
    value: 33.1,
  },
  {
    activity_id: '10',
    activity_type: 'DISABLE',
    created_at: '2024-04-10T11:09:00Z',
    value: 37.1,
  },
  {
    activity_id: '11',
    activity_type: 'PUBLISH',
    created_at: '2024-04-01T11:10:00Z',
    value: 35.1,
  },
  {
    activity_id: '12',
    activity_type: 'PUBLISH',
    created_at: '2024-04-01T11:11:00Z',
    value: 37.1,
  },
  {
    activity_id: '13',
    activity_type: 'ENABLE',
    created_at: '2024-04-01T11:12:00Z',
    value: 33.1,
  },
  {
    activity_id: '14',
    activity_type: 'PUBLISH',
    created_at: '2024-04-01T12:00:00Z',
    value: 43.1,
  },
  {
    activity_id: '15',
    activity_type: 'DISABLE',
    created_at: '2024-04-01T12:01:00Z',
    value: 35.1,
  },
  {
    activity_id: '16',
    activity_type: 'PUBLISH',
    created_at: '2024-04-01T12:02:00Z',
    value: 40.1,
  },
  {
    activity_id: '17',
    activity_type: 'DISABLE',
    created_at: '2024-04-01T12:03:00Z',
    value: 40.1,
  },
  {
    activity_id: '18',
    activity_type: 'PUBLISH',
    created_at: '2024-04-01T12:04:00Z',
    value: 40.1,
  },
  {
    activity_id: '19',
    activity_type: 'ENABLE',
    created_at: '2024-04-01T12:05:00Z',
    value: 40.1,
  },
  {
    activity_id: '20',
    activity_type: 'PUBLISH',
    created_at: '2024-04-01T12:06:00Z',
    value: 36.1,
  },
  {
    activity_id: '21',
    activity_type: 'PUBLISH',
    created_at: '2024-04-01T12:07:00Z',
    value: 39.1,
  },
  {
    activity_id: '22',
    activity_type: 'DISABLE',
    created_at: '2024-04-01T13:00:00Z',
    value: 33.1,
  },
  {
    activity_id: '23',
    activity_type: 'ENABLE',
    created_at: '2024-04-01T13:01:00Z',
    value: 31.1,
  },
  {
    activity_id: '24',
    activity_type: 'DISABLE',
    created_at: '2024-04-01T13:02:00Z',
    value: 36.1,
  },
  {
    activity_id: '25',
    activity_type: 'PUBLISH',
    created_at: '2024-04-01T13:03:00Z',
    value: 37.1,
  },
  {
    activity_id: '26',
    activity_type: 'ENABLE',
    created_at: '2024-04-01T13:04:00Z',
    value: 26.1,
  },
  {
    activity_id: '27',
    activity_type: 'PUBLISH',
    created_at: '2024-04-01T13:05:00Z',
    value: 36.1,
  },
];
const data: SensorData[] = data1.map((activity) => ({
  ...activity,
  created_at: moment(activity.created_at).format('DD/MM/YYYY HH:mm:ss'),
}));

export type SensorData = {
  activity_id: string;
  activity_type: 'ENABLE' | 'DISABLE' | 'PUBLISH';
  value: number;
  created_at: any;
};

export const columns: ColumnDef<SensorData>[] = [
  {
    id: 'select',
    header: ({ table }) => (
      <Checkbox
        checked={
          table.getIsAllPageRowsSelected() ||
          (table.getIsSomePageRowsSelected() && 'indeterminate')
        }
        onCheckedChange={(value) => table.toggleAllPageRowsSelected(!!value)}
        aria-label='Select all'
      />
    ),
    cell: ({ row }) => (
      <Checkbox
        checked={row.getIsSelected()}
        onCheckedChange={(value) => row.toggleSelected(!!value)}
        aria-label='Select row'
      />
    ),
    enableSorting: false,
    enableHiding: false,
  },
  {
    accessorKey: 'activity_id',
    header: 'ID',
    cell: ({ row }) => <div>{row.getValue('activity_id')}</div>,
  },
  {
    accessorKey: 'activity_type',
    header: 'Type',
    cell: ({ row }) => <div>{row.getValue('activity_type')}</div>,
  },
  {
    accessorKey: 'value',
    header: ({ column }) => {
      return (
        <Button
          className='p-0'
          variant='ghost'
          onClick={() => column.toggleSorting(column.getIsSorted() === 'asc')}
        >
          Value
          <ArrowUpDown className='ml-2 h-4 w-4' />
        </Button>
      );
    },
    cell: ({ row }) => <div>{row.getValue('value')}</div>,
  },
  {
    accessorKey: 'created_at',
    header: 'Created At',
    cell: ({ row }) => <div>{row.getValue('created_at')}</div>,
  },
  // {
  //   accessorKey: 'warning',
  //   header: 'Warning',
  //   cell: ({ row }) => {
  //     if (row.getValue('value') > 40) {
  //       return <div>{row.getValue('created_at')}</div>;
  //     }
  //   },
  // },
  {
    id: 'actions',
    enableHiding: false,
    cell: ({ row }) => {
      const sensorData = row.original;

      return (
        <DropdownMenu>
          <DropdownMenuTrigger asChild>
            <Button variant='ghost' className='h-8 w-8 p-0'>
              <span className='sr-only'>Open menu</span>
              <MoreHorizontal className='h-4 w-4' />
            </Button>
          </DropdownMenuTrigger>
          <DropdownMenuContent align='end'>
            <DropdownMenuLabel>Actions</DropdownMenuLabel>
            <DropdownMenuItem
              onClick={() =>
                navigator.clipboard.writeText(sensorData.activity_id)
              }
            >
              Copy ID
            </DropdownMenuItem>
            <DropdownMenuSeparator />
          </DropdownMenuContent>
        </DropdownMenu>
      );
    },
  },
];

export function DetailTable() {
  const [sorting, setSorting] = React.useState<SortingState>([]);
  const [columnFilters, setColumnFilters] = React.useState<ColumnFiltersState>(
    []
  );
  const [columnVisibility, setColumnVisibility] =
    React.useState<VisibilityState>({});
  const [rowSelection, setRowSelection] = React.useState({});

  const table = useReactTable({
    data,
    columns,
    onSortingChange: setSorting,
    onColumnFiltersChange: setColumnFilters,
    getCoreRowModel: getCoreRowModel(),
    getPaginationRowModel: getPaginationRowModel(),
    getSortedRowModel: getSortedRowModel(),
    getFilteredRowModel: getFilteredRowModel(),
    onColumnVisibilityChange: setColumnVisibility,
    onRowSelectionChange: setRowSelection,
    state: {
      sorting,
      columnFilters,
      columnVisibility,
      rowSelection,
    },
  });

  return (
    <div className='w-full'>
      <div className='flex items-center pb-4'>
        <Input
          placeholder='Filter create at...'
          value={
            (table.getColumn('created_at')?.getFilterValue() as string) ?? ''
          }
          onChange={(event) =>
            table.getColumn('created_at')?.setFilterValue(event.target.value)
          }
          className='max-w-sm'
        />
        <DropdownMenu>
          <DropdownMenuTrigger asChild>
            <Button variant='outline' className='ml-auto'>
              Columns <ChevronDown className='ml-2 h-4 w-4' />
            </Button>
          </DropdownMenuTrigger>
          <DropdownMenuContent align='end'>
            {table
              .getAllColumns()
              .filter((column) => column.getCanHide())
              .map((column) => {
                return (
                  <DropdownMenuCheckboxItem
                    key={column.id}
                    className='capitalize'
                    checked={column.getIsVisible()}
                    onCheckedChange={(value) =>
                      column.toggleVisibility(!!value)
                    }
                  >
                    {column.id}
                  </DropdownMenuCheckboxItem>
                );
              })}
          </DropdownMenuContent>
        </DropdownMenu>
      </div>
      <div className='rounded-md border'>
        <Table>
          <TableHeader>
            {table.getHeaderGroups().map((headerGroup) => (
              <TableRow key={headerGroup.id}>
                {headerGroup.headers.map((header) => {
                  return (
                    <TableHead key={header.id}>
                      {header.isPlaceholder
                        ? null
                        : flexRender(
                            header.column.columnDef.header,
                            header.getContext()
                          )}
                    </TableHead>
                  );
                })}
              </TableRow>
            ))}
          </TableHeader>
          <TableBody>
            {table.getRowModel().rows?.length ? (
              table.getRowModel().rows.map((row) => (
                <TableRow
                  key={row.id}
                  data-state={row.getIsSelected() && 'selected'}
                >
                  {row.getVisibleCells().map((cell) => (
                    <TableCell key={cell.id}>
                      {flexRender(
                        cell.column.columnDef.cell,
                        cell.getContext()
                      )}
                    </TableCell>
                  ))}
                </TableRow>
              ))
            ) : (
              <TableRow>
                <TableCell
                  colSpan={columns.length}
                  className='h-24 text-center'
                >
                  No results.
                </TableCell>
              </TableRow>
            )}
          </TableBody>
        </Table>
      </div>
      <div className='flex items-center justify-end space-x-2 py-4'>
        <div className='flex-1 text-sm text-muted-foreground'>
          {table.getFilteredSelectedRowModel().rows.length} of{' '}
          {table.getFilteredRowModel().rows.length} row(s) selected.
        </div>
        <div className='space-x-2'>
          <Button
            variant='outline'
            size='sm'
            onClick={() => table.previousPage()}
            disabled={!table.getCanPreviousPage()}
          >
            Previous
          </Button>
          <Button
            variant='outline'
            size='sm'
            onClick={() => table.nextPage()}
            disabled={!table.getCanNextPage()}
          >
            Next
          </Button>
        </div>
      </div>
    </div>
  );
}
