/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008 INRIA
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as 
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */
#include "wifi-mac.h"
#include "ns3/uinteger.h"

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (WifiMac);

Time
WifiMac::GetDefaultMaxPropagationDelay (void)
{
  // 1000m 
  return Seconds (1000.0 / 300000000.0);
}
Time
WifiMac::GetDefaultSlot (void)
{
  // 802.11-a specific
  return MicroSeconds (9);
}
Time
WifiMac::GetDefaultSifs (void)
{
  // 802.11-a specific
  return MicroSeconds (16);
}
Time
WifiMac::GetDefaultEifsNoDifs (void)
{
  return GetDefaultSifs () + GetDefaultCtsAckDelay ();
}
Time
WifiMac::GetDefaultCtsAckDelay (void)
{
  // 802.11-a specific: 6mb/s
  return MicroSeconds (44);
}
Time
WifiMac::GetDefaultCtsAckTimeout (void)
{
  /* Cts_Timeout and Ack_Timeout are specified in the Annex C 
     (Formal description of MAC operation, see details on the 
     Trsp timer setting at page 346)
  */
  Time ctsTimeout = GetDefaultSifs ();
  ctsTimeout += GetDefaultCtsAckDelay ();
  ctsTimeout += GetDefaultMaxPropagationDelay () * Scalar (2);
  ctsTimeout += GetDefaultSlot ();
  return ctsTimeout;
}


TypeId 
WifiMac::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::WifiMac")
    .SetParent<Object> ()
    .AddAttribute ("CtsTimeout", "XXX",
                   TimeValue (GetDefaultCtsAckTimeout ()),
                   MakeTimeAccessor (&WifiMac::m_ctsTimeout),
                   MakeTimeChecker ())
    .AddAttribute ("AckTimeout", "XXX",
                   TimeValue (GetDefaultCtsAckTimeout ()),
                   MakeTimeAccessor (&WifiMac::m_ackTimeout),
                   MakeTimeChecker ())
    .AddAttribute ("Sifs", "XXX",
                   TimeValue (GetDefaultSifs ()),
                   MakeTimeAccessor (&WifiMac::SetSifs,
				     &WifiMac::GetSifs),
                   MakeTimeChecker ())
    .AddAttribute ("EifsNoDifs", "XXX",
		   TimeValue (GetDefaultEifsNoDifs ()),
		   MakeTimeAccessor (&WifiMac::SetEifsNoDifs,
				     &WifiMac::GetEifsNoDifs),
		   MakeTimeChecker ())
    .AddAttribute ("Slot", "XXX",
                   TimeValue (GetDefaultSlot ()),
                   MakeTimeAccessor (&WifiMac::SetSlot,
				     &WifiMac::GetSlot),
                   MakeTimeChecker ())
    .AddAttribute ("Pifs", "XXX",
                   TimeValue (GetDefaultSifs () + GetDefaultSlot ()),
                   MakeTimeAccessor (&WifiMac::m_pifs),
                   MakeTimeChecker ())
    .AddAttribute ("MaxPropagationDelay", "XXX",
                   TimeValue (GetDefaultMaxPropagationDelay ()),
                   MakeTimeAccessor (&WifiMac::m_maxPropagationDelay),
                   MakeTimeChecker ())
    .AddAttribute ("MaxMsduSize", "XXX",
		   UintegerValue (2304),
		   MakeUintegerAccessor (&WifiMac::m_maxMsduSize),
		   MakeUintegerChecker<uint16_t> (1,2304))
    .AddAttribute ("Ssid", "XXX",
		   SsidValue (Ssid ("default")),
		   MakeSsidAccessor (&WifiMac::GetSsid,
				     &WifiMac::SetSsid),
		   MakeSsidChecker ())
    ;
  return tid;
}

void
WifiMac::SetPifs (Time pifs)
{
  m_pifs = pifs;
}
void 
WifiMac::SetCtsTimeout (Time ctsTimeout)
{
  m_ctsTimeout = ctsTimeout;
}
void 
WifiMac::SetAckTimeout (Time ackTimeout)
{
  m_ackTimeout = ackTimeout;
}
void 
WifiMac::SetMaxPropagationDelay (Time delay)
{
  m_maxPropagationDelay = delay;
}
Time
WifiMac::GetPifs (void) const
{
  return m_pifs;
}
Time
WifiMac::GetCtsTimeout (void) const
{
  return m_ctsTimeout;
}
Time
WifiMac::GetAckTimeout (void) const
{
  return m_ackTimeout;
}

Time
WifiMac::GetMsduLifetime (void) const
{
  return Seconds (10);
}
Time
WifiMac::GetMaxPropagationDelay (void) const
{
  return m_maxPropagationDelay;
}

uint32_t 
WifiMac::GetMaxMsduSize (void) const
{
  return m_maxMsduSize;
}


} // namespace ns3