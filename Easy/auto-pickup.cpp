#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>

using namespace std;

#define ID101      5
#define HDR_LENGTH 3
#define ITM_LENGTH 4

class CG_PACKET 
{
    private:
        uint8_t  m_length;  /*!< Length of the packet  */
        string   m_str;     /*!< String representation */

    private:
        void parseHeader(uint8_t& p_pos,
                         bool&    p_okHdr,
                         string&  p_txt) const
        {
            uint8_t l_ret(0);

            if  ( p_pos+1 >= HDR_LENGTH )
            {
                l_ret = ( ( ( (m_str[p_pos   ] == '1') & 1) << 2 ) +
                          ( ( (m_str[p_pos -1] == '1') & 1) << 1 ) +
                          ( ( (m_str[p_pos -2] == '1') & 1) << 0 ) );
                p_pos = (p_pos+1 == HDR_LENGTH) ? 0 : (p_pos - HDR_LENGTH);
            }
            else
            {
                p_pos = 0;
            }

            p_okHdr = (l_ret == ID101);

            if ( p_okHdr )
            {
                p_txt += "001";
            }
        }

        void parseLength(uint8_t& p_pos, 
                         uint8_t& p_length, 
                         bool     p_okHdr,
                         string&  p_txt) const
        {
            if ( p_pos+1 >= ITM_LENGTH )
            {
                p_length = ( ( ( (m_str[p_pos   ] == '1') & 1) << 3 ) +
                             ( ( (m_str[p_pos -1] == '1') & 1) << 2 ) +
                             ( ( (m_str[p_pos -2] == '1') & 1) << 1 ) +
                             ( ( (m_str[p_pos -3] == '1') & 1) << 0 ) );
                p_pos =(p_pos+1 == ITM_LENGTH) ? 0 : (p_pos - ITM_LENGTH);
            }
            else
            {
                p_pos = 0;
            }

            if ( p_okHdr )
            {
                for ( int i = 0; i < ITM_LENGTH; i++ )
                {
                    p_txt += ( p_length & (1 << (ITM_LENGTH -1 -i)) ) ? '1' : '0';
                }
            }
        }

        void parsePayLoad(uint8_t& p_pos, 
                          uint8_t  p_length,
                          bool     p_okHdr,
                          string&  p_txt) const
        {
            if ( p_pos+1 >= p_length )
            {
                if ( p_okHdr )
                {
                    for ( uint8_t i = 0; i < p_length; i++ )
                    {
                        p_txt += m_str[p_pos -i];
                    }
                }
                p_pos = (p_pos+1 == p_length) ? 0 : (p_pos - p_length);
            }
            else
            {
                p_pos = 0;
            }
        }

    public:
        CG_PACKET(): m_length(0), m_str("") {}

        // Receive function
        void rcv(void)
        {
            int    l_length;
            cin >> l_length >> m_str; cin.ignore();

            reverse(m_str.begin(), m_str.end());
            m_length = static_cast<uint8_t>(l_length);
        }

        // Decode function
        string dcd(void)
        {
            string  l_ret;
            uint8_t l_curPos(m_length - 1), l_length(0);
            bool    l_okHdr (false);

            while( l_curPos > 0 )
            {
                parseHeader (l_curPos,           l_okHdr, l_ret);
                parseLength (l_curPos, l_length, l_okHdr, l_ret);
                parsePayLoad(l_curPos, l_length, l_okHdr, l_ret);
            }

            return l_ret;
        }
};

int main()
{
    CG_PACKET packet;

    packet.rcv();

    cout << packet.dcd() << endl;
}