import unittest
import subprocess
import tempfile


exe = './ft_ssl'


class BaseTestCase(unittest.TestCase):

    def noinput(self):

        a = subprocess.run([f'{exe}'], capture_output=True)
        b = subprocess.run(['openssl'], capture_output=True)

        self.assertEqual(a.stdout, b.stdout)
        self.assertEqual(a.stderr, b.stderr)

    def wrongcmd(self):

        cmd = 'foobar'
        a = subprocess.run([f'{exe}', f'{cmd}'], capture_output=True)
        b = f'''
        ft_ssl: Error: \'{cmd}\' is an invalid command.

        Standard commands:

        Message Digest commands:
        md5
        sha224
        sha256
        sha384
        sha512
        Cipher commands:
        '''

        self.assertEqual(str(a.stderr), b)


class MD5TestCase(unittest.TestCase):

    def stdin(self):

        a = subprocess.run(['echo', '"pickle rick"', '|', 'openssl', 'md5'], capture_output=True)
        b = subprocess.run(['echo', '"pickle rick"', '|', f'{exe}', 'md5'], capture_output=True)

        self.assertEqual(a.stdout, b.stdout)
        self.assertEqual(a.stderr, b.stderr)

    def stdin_p(self):

        a = subprocess.run(['echo', '"Do not pity the dead, Harry."', '|', f'{exe}', 'md5', '-p'], capture_output=True)
        b = subprocess.run(['echo', '"Do not pity the dead, Harry."', '|', 'md5', '-p'], capture_output=True)

        self.assertEqual(a.stdout, b.stdout)
        self.assertEqual(a.stderr, b.stderr)

    def stdin_qr(self):

        a = subprocess.run(['echo', '"Pity the living."', '|', f'{exe}', 'md5', '-q', '-r'], capture_output=True)
        b = subprocess.run(['echo', '"Pity the living."', '|', 'md5', '-q', '-r'], capture_output=True)

        self.assertEqual(a.stdout, b.stdout)
        self.assertEqual(a.stderr, b.stderr)

    def file_empty(self):

        with tempfile.NamedTemporaryFile() as f:

            a = subprocess.run([f'{exe}', 'md5', f'{f.name}'], capture_output=True)
            b = subprocess.run(['md5', f'{f.name}'], capture_output=True)

        self.assertEqual(a.stdout, b.stdout)
        self.assertEqual(a.stderr, b.stderr)

    def file(self):

        with tempfile.NamedTemporaryFile() as f:

            subprocess.run(['echo', '"And above all,"', '>', f'{f.name}'])
            a = subprocess.run([f'{exe}', 'md5', f'{f.name}'], capture_output=True)
            b = subprocess.run(['md5', f'{f.name}'], capture_output=True)

        self.assertEqual(a.stdout, b.stdout)
        self.assertEqual(a.stderr, b.stderr)

    def file_r(self):

        with tempfile.NamedTemporaryFile() as f:

            subprocess.run(['echo', '"And above all,"', '>', f'{f.name}'])
            a = subprocess.run([f'{exe}', 'md5', '-r', f'{f.name}'], capture_output=True)
            b = subprocess.run(['md5', '-r', f'{f.name}'], capture_output=True)

        self.assertEqual(a.stdout, b.stdout)
        self.assertEqual(a.stderr, b.stderr)

    def string_empty(self):

        str = '""'
        a = subprocess.run([f'{exe}', 'md5', '-s', f'{str}'], capture_output=True)
        b = subprocess.run(['md5', '-s', f'{str}'], capture_output=True)

        self.assertEqual(a.stdout, b.stdout)
        self.assertEqual(a.stderr, b.stderr)

    def string(self):

        str = '"pity those that aren\'t following baerista on spotify."'
        a = subprocess.run([f'{exe}', 'md5', '-s', f'{str}'], capture_output=True)
        b = subprocess.run(['md5', '-s', f'{str}'], capture_output=True)

        self.assertEqual(a.stdout, b.stdout)
        self.assertEqual(a.stderr, b.stderr)

    def stdin_file(self):

        with tempfile.NamedTemporaryFile() as f:

            subprocess.run(['echo', '"And above all,"', '>', f'{f.name}'])
            a = subprocess.run(['echo', '"some of this will not make sense at first"', '|', f'{exe}', 'md5', f'{f.name}'], capture_output=True)
            b = subprocess.run(['echo', '"some of this will not make sense at first"', '|', 'md5', f'{f.name}'], capture_output=True)

        self.assertEqual(a.stdout, b.stdout)
        self.assertEqual(a.stderr, b.stderr)

    def stdin_file_p(self):

        with tempfile.NamedTemporaryFile() as f:

            subprocess.run(['echo', '"And above all,"', '>', f'{f.name}'])
            a = subprocess.run(['echo', '"be sure to handle edge cases carefully"', '|', f'{exe}', 'md5', '-p', f'{f.name}'], capture_output=True)
            b = subprocess.run(['echo', '"be sure to handle edge cases carefully"', '|', 'md5', '-p', f'{f.name}'], capture_output=True)

        self.assertEqual(a.stdout, b.stdout)
        self.assertEqual(a.stderr, b.stderr)

    def stdin_file_pr(self):

        with tempfile.NamedTemporaryFile() as f:

            subprocess.run(['echo', '"And above all,"', '>', f'{f.name}'])
            a = subprocess.run(['echo', '"but eventually you will understand"', '|', f'{exe}', 'md5', '-p', '-r', f'{f.name}'], capture_output=True)
            b = subprocess.run(['echo', '"but eventually you will understand"', '|', 'md5', '-p', '-r', f'{f.name}'], capture_output=True)

        self.assertEqual(a.stdout, b.stdout)
        self.assertEqual(a.stderr, b.stderr)

    def stdin_file_string_p(self):

        with tempfile.NamedTemporaryFile() as f:

            str = '"foo"'
            subprocess.run(['echo', '"And above all,"', '>', f'{f.name}'])
            a = subprocess.run(['echo', '"GL HF let\'s go"', '|', f'{exe}', 'md5', '-p', '-s', f'{str}', f'{f.name}'], capture_output=True)
            b = subprocess.run(['echo', '"GL HF let\'s go"', '|', 'md5', '-p', '-s', f'{str}', f'{f.name}'], capture_output=True)

        self.assertEqual(a.stdout, b.stdout)
        self.assertEqual(a.stderr, b.stderr)

    def stdin_file_string_rp(self):

        with tempfile.NamedTemporaryFile() as f:

            str1 = '"foo"'
            str2 = '"bar"'
            subprocess.run(['echo', '"And above all,"', '>', f'{f.name}'])
            a = subprocess.run(['echo', '"one more thing"', '|', f'{exe}', 'md5', '-r', '-p', '-s', f'{str1}', f'{f.name}', '-s', f'{str2}'], capture_output=True)
            b = subprocess.run(['echo', '"one more thing"', '|', 'md5', '-r', '-p', '-s', f'{str1}', f'{f.name}', '-s', f'{str2}'], capture_output=True)

        self.assertEqual(a.stdout, b.stdout)
        self.assertEqual(a.stderr, b.stderr)

    def stdin_file_string_rqp(self):

        with tempfile.NamedTemporaryFile() as f:

            str = '"foo"'
            subprocess.run(['echo', '"And above all,"', '>', f'{f.name}'])
            a = subprocess.run(['echo', '"just to be extra clear"', '|', f'{exe}', 'md5', '-r', '-q', '-p', '-s', f'{str}', f'{f.name}'], capture_output=True)
            b = subprocess.run(['echo', '"just to be extra clear"', '|', 'md5', '-r', '-q', '-p', '-s', f'{str}', f'{f.name}'], capture_output=True)

        self.assertEqual(a.stdout, b.stdout)
        self.assertEqual(a.stderr, b.stderr)

if __name__ == '__main__':
    unittest.main()
