package com.util.dns;

/**
 * 
 * @author JasonZhao
 *
 */
public class DnsUtil {

  public native String getTxtRecord(String host);

  public native String getARecord(String domainName, String server);

  public native String getPtrRecord(String reverseIp, String server);
}
