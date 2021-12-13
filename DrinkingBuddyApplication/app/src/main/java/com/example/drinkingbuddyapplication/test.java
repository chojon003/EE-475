package com.example.drinkingbuddyapplication;

import android.Manifest;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
import android.content.Context;
import android.content.pm.PackageManager;
import android.location.LocationManager;
import android.os.Build;
import android.util.Log;
import android.widget.Button;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import com.clj.fastble.BleManager;
import com.clj.fastble.callback.BleGattCallback;
import com.clj.fastble.callback.BleReadCallback;
import com.clj.fastble.callback.BleScanCallback;
import com.clj.fastble.data.BleDevice;
import com.clj.fastble.exception.BleException;

import java.util.ArrayList;
import java.util.List;

public class test {
//    //BLE
//    private void startScan() {
//        BleManager.getInstance().scan(new BleScanCallback() {
//            @Override
//            public void onScanStarted(boolean success) {
//                bleDeviceAdapter.clear();
//                bleDeviceAdapter.notifyDataSetChanged();
//                dialogBuilder.show();
//
//            }
//
//            @Override
//            public void onLeScan(BleDevice bleDevice) {
//                super.onLeScan(bleDevice);
//            }
//
//            @Override
//            public void onScanning(BleDevice bleDevice) {
//                bleDeviceAdapter.add(bleDevice);
//                bleDeviceAdapter.notifyDataSetChanged();
//            }
//
//            @Override
//            public void onScanFinished(List<BleDevice> scanResultList) {
//
//            }
//        });
//    }
//
//    private void connect(final BleDevice bleDevice) {
//
//
//        BleManager.getInstance().connect(bleDevice, new BleGattCallback() {
//            @Override
//            public void onStartConnect() {
//            }
//
//            @Override
//            public void onConnectFail(BleDevice bleDevice, BleException exception) {
//                Toast.makeText(getActivity(), "Failed to connect.", Toast.LENGTH_LONG).show();
//            }
//
//            @Override
//            public void onConnectSuccess(BleDevice bleDevice, BluetoothGatt gatt, int status) {
//                activeBleDevice = bleDevice;
//
//                Toast.makeText(getActivity(), "Connected.", Toast.LENGTH_LONG).show();
//
//                Button selectDeviceButton = (Button) getActivity().findViewById(R.id.devices);
//                selectDeviceButton.setText("Connected to: " + activeBleDevice.getName());
//
//                BluetoothGattCharacteristic notifyCharacteristic = null;
//
//                for (BluetoothGattService bgs: gatt.getServices()) {
//                    if (bgs.getUuid().toString().equals("6e400001-b5a3-f393-e0a9-e50e24dcca9e")) {
//                        Log.d("Service", bgs.getUuid() + "");
//                        for (BluetoothGattCharacteristic bgc : bgs.getCharacteristics()) {
//                            int property = bgc.getProperties();
//                            Log.d("Test", bgc.getUuid() + "," + bgc.getProperties());
//                            //if ((property & BluetoothGattCharacteristic.PROPERTY_READ) > 0) {
//                            notifyCharacteristic = bgc;
//                            //}
//                        }
//                    }
//                }
//
//                BleManager.getInstance().read(
//                        bleDevice,
//                        notifyCharacteristic.getService().getUuid().toString(),
//                        notifyCharacteristic.getUuid().toString(),
//                        new BleReadCallback() {
//                            @Override
//                            public void onReadSuccess(byte[] data) {
//                                Toast.makeText(getActivity(), "read success: "+ new String(data), Toast.LENGTH_SHORT).show();
//                            }
//
//                            @Override
//                            public void onReadFailure(BleException exception) {
//                                Toast.makeText(getActivity(), "Failure", Toast.LENGTH_SHORT).show();
//
//                            }
//                        });
//
//            }
//
//            @Override
//            public void onDisConnected(boolean isActiveDisConnected, BleDevice bleDevice, BluetoothGatt gatt, int status) {
////                Button selectDeviceButton = (Button) getActivity().findViewById(R.id.devices);
////                selectDeviceButton.setText("Choose Device");
//            }
//        });
//    }
//    //Permission
//    private void checkPermissions() {
//        BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
//        if (!bluetoothAdapter.isEnabled()) {
//            Toast.makeText(getActivity(), getString(R.string.please_open_blue), Toast.LENGTH_LONG).show();
//            return;
//        }
//
//        String[] permissions = {Manifest.permission.ACCESS_FINE_LOCATION};
//        List<String> permissionDeniedList = new ArrayList<>();
//        for (String permission : permissions) {
//            int permissionCheck = ContextCompat.checkSelfPermission(getActivity(), permission);
//            if (permissionCheck == PackageManager.PERMISSION_GRANTED) {
//                onPermissionGranted(permission);
//            } else {
//                permissionDeniedList.add(permission);
//            }
//        }
//        if (!permissionDeniedList.isEmpty()) {
//            String[] deniedPermissions = permissionDeniedList.toArray(new String[permissionDeniedList.size()]);
//            ActivityCompat.requestPermissions(getActivity(), deniedPermissions, REQUEST_CODE_PERMISSION_LOCATION);
//        }
//    }
//
//    @Override
//    public final void onRequestPermissionsResult(int requestCode,
//                                                 @NonNull String[] permissions,
//                                                 @NonNull int[] grantResults) {
//        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
//        switch (requestCode) {
//            case REQUEST_CODE_PERMISSION_LOCATION:
//                if (grantResults.length > 0) {
//                    for (int i = 0; i < grantResults.length; i++) {
//                        if (grantResults[i] == PackageManager.PERMISSION_GRANTED) {
//                            onPermissionGranted(permissions[i]);
//                        }
//                    }
//                }
//                break;
//        }
//    }
//
//    private void onPermissionGranted(String permission) {
//        switch (permission) {
//            case Manifest.permission.ACCESS_FINE_LOCATION:
//                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M && !checkGPSIsOpen()) {
//                    Toast.makeText(getActivity(), "Permissions are granted", Toast.LENGTH_LONG).show();
//                } else {
//                    Toast.makeText(getActivity(), "Permissions are granted", Toast.LENGTH_LONG).show();
//                }
//                break;
//        }
//    }
//
//    private boolean checkGPSIsOpen() {
//        LocationManager locationManager = (LocationManager) getActivity().getSystemService(Context.LOCATION_SERVICE);
//        if (locationManager == null)
//            return false;
//        return locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER);
//    }
}
