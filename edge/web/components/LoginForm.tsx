'use client';

import { useState } from 'react';
import { useRouter } from 'next/navigation';
import { Button } from '@/components/ui/button';
import { Input } from '@/components/ui/input';
import { Card } from '@/components/ui/card';

const LoginForm = () => {
  const router = useRouter();
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');

  const handleSubmit = (e: React.FormEvent) => {
    e.preventDefault();
    // Xử lý logic đăng nhập tại đây
    if (email === 'admin@gmail.com' && password === '123') {
      router.push('/');
    }
    console.log({ email, password });
  };

  return (
    <Card className='max-w-md mx-auto p-4'>
      <h2 className='text-center text-xl font-semibold mb-4'>Login</h2>
      <form onSubmit={handleSubmit}>
        <div className='mb-4'>
          <Input
            type='email'
            placeholder='Email'
            value={email}
            onChange={(e: any) => setEmail(e.target.value)}
            required
            className='w-full'
          />
        </div>
        <div className='mb-4'>
          <Input
            type='password'
            placeholder='Password'
            value={password}
            onChange={(e: any) => setPassword(e.target.value)}
            required
            className='w-full'
          />
        </div>
        <Button type='submit' className='w-full'>
          Login
        </Button>
      </form>
    </Card>
  );
};

export default LoginForm;
