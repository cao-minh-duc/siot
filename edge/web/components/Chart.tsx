'use client';
import * as React from 'react';
import { Bar, BarChart, CartesianGrid, XAxis } from 'recharts';
import {
  Card,
  CardContent,
  CardDescription,
  CardHeader,
  CardTitle,
} from '@/components/ui/card';
import {
  ChartConfig,
  ChartContainer,
  ChartTooltip,
  ChartTooltipContent,
} from '@/components/ui/chart';
const chartData = [
  { date: '2024-04-01T11:00:00Z', value: 40.1 },
  { date: '2024-04-01T11:01:00Z', value: 39.1 },
  { date: '2024-04-01T11:02:00Z', value: 38.1 },
  { date: '2024-04-01T11:03:00Z', value: 37.1 },
  { date: '2024-04-01T11:04:00Z', value: 41.1 },
  { date: '2024-04-01T11:05:00Z', value: 42.1 },
  { date: '2024-04-01T11:06:00Z', value: 35.1 },
  { date: '2024-04-01T11:07:00Z', value: 30.1 },
  { date: '2024-04-01T11:08:00Z', value: 33.1 },
  { date: '2024-04-01T11:09:00Z', value: 37.1 },
  { date: '2024-04-01T11:10:00Z', value: 35.1 },
  { date: '2024-04-01T11:11:00Z', value: 37.1 },
  { date: '2024-04-01T11:12:00Z', value: 33.1 },
  { date: '2024-04-01T12:00:00Z', value: 43.1 },
  { date: '2024-04-01T12:01:00Z', value: 35.1 },
  { date: '2024-04-01T12:02:00Z', value: 40.1 },
  { date: '2024-04-01T12:03:00Z', value: 40.1 },
  { date: '2024-04-01T12:04:00Z', value: 40.1 },
  { date: '2024-04-01T12:05:00Z', value: 40.1 },
  { date: '2024-04-01T12:06:00Z', value: 36.1 },
  { date: '2024-04-01T12:07:00Z', value: 39.1 },
  { date: '2024-04-01T13:00:00Z', value: 33.1 },
  { date: '2024-04-01T13:01:00Z', value: 31.1 },
  { date: '2024-04-01T13:02:00Z', value: 36.1 },
  { date: '2024-04-01T13:03:00Z', value: 37.1 },
  { date: '2024-04-01T13:04:00Z', value: 26.1 },
  { date: '2024-04-01T13:05:00Z', value: 36.1 },
];
const chartConfig = {
  views: {
    label: 'Value',
  },
  value: {
    label: 'Value',
    color: 'hsl(var(--chart-1))',
  },
} satisfies ChartConfig;
export function Chart() {
  const [activeChart, setActiveChart] =
    React.useState<keyof typeof chartConfig>('value');
  const total = React.useMemo(
    () => ({
      value: chartData.reduce((acc, curr) => acc + curr.value, 0),
    }),
    []
  );
  return (
    <Card className='mb-4'>
      <CardHeader className='flex flex-col items-stretch space-y-0 border-b p-0 sm:flex-row '>
        <div className='flex flex-1 flex-col justify-center gap-1 px-6 py-5 sm:py-6'>
          <CardTitle>Sensor chart</CardTitle>
          <CardDescription>
            Showing value of sensor for the last 3 hours
          </CardDescription>
        </div>
        <div className='flex'>
          {['value'].map((key) => {
            const chart = key as keyof typeof chartConfig;
            const average = total[key as keyof typeof total] / chartData.length;
            return (
              <button
                key={chart}
                data-active={activeChart === chart}
                className='relative z-30 flex flex-1 flex-col justify-center gap-1 border-t px-6 py-4 text-left even:border-l data-[active=true]:bg-muted/50 sm:border-l sm:border-t-0 sm:px-8 sm:py-6'
                onClick={() => setActiveChart(chart)}
              >
                <span className='text-xs text-muted-foreground'>Average</span>
                <span className='text-lg font-bold leading-none sm:text-3xl'>
                  {parseFloat(average.toFixed(2))}
                </span>
              </button>
            );
          })}
        </div>
      </CardHeader>
      <CardContent className='px-2 sm:p-6'>
        <ChartContainer
          config={chartConfig}
          className='aspect-auto h-[250px] w-full'
        >
          <BarChart
            accessibilityLayer
            data={chartData}
            margin={{
              left: 12,
              right: 12,
            }}
          >
            <CartesianGrid vertical={false} />
            <XAxis
              dataKey='date'
              tickLine={false}
              axisLine={false}
              tickMargin={8}
              minTickGap={32}
              tickFormatter={(value: any) => {
                const date = new Date(value);
                return date.toLocaleDateString('en-US', {
                  month: 'short',
                  day: 'numeric',
                  hour: '2-digit',
                  minute: '2-digit',
                });
              }}
            />
            <ChartTooltip
              content={
                <ChartTooltipContent
                  className='w-[150px]'
                  nameKey='views'
                  labelFormatter={(value: any) => {
                    return new Date(value).toLocaleDateString('en-US', {
                      month: 'short',
                      day: 'numeric',
                      year: 'numeric',
                      hour: '2-digit',
                      minute: '2-digit',
                    });
                  }}
                />
              }
            />
            <Bar dataKey={activeChart} fill={`var(--color-${activeChart})`} />
          </BarChart>
        </ChartContainer>
      </CardContent>
    </Card>
  );
}
