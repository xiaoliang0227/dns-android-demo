package com.util.dns;

import android.app.Activity;
import android.content.Context;
import android.net.DhcpInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.example.myndk2.R;

/**
 * 
 * @author JasonZhao
 *
 */
public class MainActivity extends Activity {

  private static final String TAG = "MainActivity";

  private EditText input;

  private TextView display;

  private String gateway;

  static {
    System.loadLibrary("dnsutil");
  }

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);
    input = (EditText) findViewById(R.id.input);
    display = (TextView) findViewById(R.id.display);
    gateway = getGateway(this);
  }

  public void testTxtRecord(View view) {
    if (TextUtils.isEmpty(input.getText())) {
      Toast.makeText(this, "请输入查询内容", Toast.LENGTH_LONG).show();
      return;
    }
    DnsUtil du = new DnsUtil();
    String res = du.getTxtRecord(input.getText().toString());
    display.setText(null == res ? "没有查询到任何结果" : res);
  }

  public void testARecord(View view) {
    if (TextUtils.isEmpty(input.getText())) {
      Toast.makeText(this, "请输入查询内容", Toast.LENGTH_LONG).show();
      return;
    }
    DnsUtil du = new DnsUtil();
    String res = du.getARecord(input.getText().toString(), gateway);
    display.setText(null == res ? "没有查询到任何结果" : res);
  }

  public void testPtrRecord(View view) {
    if (TextUtils.isEmpty(input.getText())) {
      Toast.makeText(this, "请输入查询内容", Toast.LENGTH_LONG).show();
      return;
    }
    DnsUtil du = new DnsUtil();
    String res = du.getPtrRecord(
        String.format("%s.in-addr.arpa", ipReverse(gateway)), gateway);
    display.setText(null == res ? "没有查询到任何结果" : res);
  }

  public String getGateway(Context context) {
    WifiManager wm = (WifiManager) context
        .getSystemService(Context.WIFI_SERVICE);
    DhcpInfo dhcpInfo = wm.getDhcpInfo();
    return getIpAddress(dhcpInfo.gateway);
  }

  public String getIpAddress(int ip) {
    String ipString = "";
    if (ip != 0) {
      ipString = ((ip & 0xff) + "." + (ip >> 8 & 0xff) + "."
          + (ip >> 16 & 0xff) + "." + (ip >> 24 & 0xff));
    }
    return ipString;
  }

  public String ipReverse(String ip) {
    String[] parts = ip.split("\\.");
    StringBuilder sb = new StringBuilder();
    for (int i = parts.length - 1; i >= 0; i--) {
      sb.append(parts[i]).append(".");
    }
    if (sb.length() > 0) {
      sb.setLength(sb.length() - 1);
    }
    return sb.toString();
  }
}
