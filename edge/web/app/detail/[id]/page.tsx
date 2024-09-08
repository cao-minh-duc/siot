import { DetailTable } from '../../../components/DetailTable';
import { Chart } from '../../../components/Chart';

export default function LoginPage({ params }: { params: { id: string } }) {
  return (
    <div>
      <Chart />
      <DetailTable />
    </div>
  );
}
