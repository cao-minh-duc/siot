'use client';
import { DataTable } from '@/components/DataTable';
import { Header } from '@/components/Header';
import { useRouter } from 'next/navigation';
import { useEffect } from 'react';

export default function Home() {
  const router = useRouter();

  return (
    <div>
      <h1 className='text-3xl font-bold mb-5'>Sensor Management</h1>
      <DataTable />
    </div>
  );
}
