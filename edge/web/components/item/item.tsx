import * as React from 'react';

import { Button } from '@/components/ui/button';
import Image from 'next/image';
import profilePic from '../../arduino.jpg';
import {
  Card,
  CardContent,
  CardDescription,
  CardFooter,
  CardHeader,
  CardTitle,
} from '@/components/ui/card';
import './item.css';

export function Item() {
  return (
    <div className='wrapper'>
      {Array.from({ length: 10 }, (_, index) => (
        <Card className='box' key={index}>
          <CardHeader>
            <CardTitle>Fire Sensor</CardTitle>
            <CardDescription>
              <p>Location: Da Lat</p>
              <p>Status: On</p>
            </CardDescription>
          </CardHeader>
          <CardContent>
            <form>
              <div className='grid w-full items-center gap-4'></div>
            </form>
          </CardContent>
          <CardFooter className='justify-end mt-4'>
            <Button>Rent</Button>
          </CardFooter>
        </Card>
      ))}
    </div>
  );
}
