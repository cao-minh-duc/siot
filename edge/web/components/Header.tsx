import Link from 'next/link';
import {
  DropdownMenu,
  DropdownMenuContent,
  DropdownMenuItem,
  DropdownMenuTrigger,
} from '@/components/ui/dropdown-menu';

import { LogOut, Users } from 'lucide-react';

export function Header() {
  return (
    <div className='flex justify-between px-10 py-4 bg-gray-400 fixed top-0 w-full z-50'>
      <div className='flex gap-10'>
        <Link href={'/'}>Home</Link>
        <Link href={'/rent'}>Sensor rental</Link>
      </div>

      <DropdownMenu>
        <DropdownMenuTrigger asChild>
          <Users />
        </DropdownMenuTrigger>
        <DropdownMenuContent className='mr-5'>
          <DropdownMenuItem>
            <Link href={'/login'} className='flex justify-between items-center'>
              <LogOut className='mr-2 h-4 w-4' />
              <span>Log out</span>
            </Link>
          </DropdownMenuItem>
        </DropdownMenuContent>
      </DropdownMenu>
    </div>
  );
}
