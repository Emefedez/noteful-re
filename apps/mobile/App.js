import React, {useEffect, useRef, useState} from 'react';
import {ActivityIndicator, StyleSheet, Text, View, Pressable, useColorScheme, Linking} from 'react-native';
import {SafeAreaProvider, SafeAreaView} from 'react-native-safe-area-context';
import {StatusBar} from 'expo-status-bar';
import Constants from 'expo-constants';
import {WebView} from 'react-native-webview';
import * as FileSystem from 'expo-file-system/legacy';
import * as Sharing from 'expo-sharing';
import {IncomingFiles} from './incoming-files.mjs';
import {readerURL, exportRequest, allowsNavigation} from './connection.mjs';

export default function App() {
 const web = useRef(null), sharing = useRef(false), incoming = useRef(null);
 const [error, setError] = useState(''), [attempt, setAttempt] = useState(0);
 const dark = useColorScheme() === 'dark';
 const background = dark ? '#1c2839' : '#f1f5f9', ink = dark ? '#e8eef8' : '#202d40';
 let uri, configError;
 try { uri = readerURL(process.env.EXPO_PUBLIC_READER_URL, Constants.expoConfig?.hostUri, Constants.expoConfig?.extra?.readerPort); }
 catch (e) { configError = e.message; }
 if(!incoming.current)incoming.current=new IncomingFiles({read:uri=>FileSystem.readAsStringAsync(uri,{encoding:FileSystem.EncodingType.Base64}),post:message=>web.current?.postMessage(JSON.stringify(message)),error:e=>setError('Could not read the opened file: '+e.message)});
 useEffect(()=>{const subscription=Linking.addEventListener('url',event=>incoming.current.open(event.url));Linking.getInitialURL().then(url=>incoming.current.open(url)).catch(e=>setError(e.message));return()=>subscription.remove();},[]);
 const reply = result => web.current?.postMessage(JSON.stringify({type:'noteful-export-result', ...result}));
 async function onMessage(event) {
  let request;
  try {
   if(!allowsNavigation(event.nativeEvent.url,uri)||event.nativeEvent.url==='about:blank')return;
   const message=JSON.parse(event.nativeEvent.data);
   if(message.type==='noteful-ready'){incoming.current.setReady(true);return;}
   if(message.type==='noteful-import-result'){incoming.current.acknowledge(message.id);return;}
   request = exportRequest(event.nativeEvent.data, event.nativeEvent.url, uri);
   if (sharing.current) throw Error('Finish saving the previous file first.');
   sharing.current = true;
   try {
    if (!await Sharing.isAvailableAsync()) throw Error('File sharing is not available.');
    const directory = `${FileSystem.cacheDirectory}noteful-${Date.now()}-${request.id}/`;
    await FileSystem.makeDirectoryAsync(directory, {intermediates:true});
    const file = directory + request.name;
    await FileSystem.writeAsStringAsync(file, request.base64, {encoding:FileSystem.EncodingType.Base64});
    await Sharing.shareAsync(file, {mimeType:request.mime || 'application/octet-stream', dialogTitle:'Save a copy'});
    reply({id:request.id});
   } finally { sharing.current = false; }
  } catch (e) { if (request) reply({id:request.id,error:e.message}); }
 }
 return <SafeAreaProvider><SafeAreaView style={[styles.root,{backgroundColor:background}]}>
  <StatusBar style={dark ? 'light' : 'dark'}/>
  {error || configError ? <View style={styles.message}>
   <Text style={[styles.title,{color:ink}]}>Your notebook is within reach.</Text>
   <Text style={[styles.description,{color:ink}]}>Keep your computer and phone on the same Wi-Fi, with the reader running on your computer.</Text>
   <Text selectable style={[styles.detail,{color:ink}]}>{error || configError}</Text>
   <Pressable accessibilityRole="button" style={styles.retry} onPress={()=>{setError('');setAttempt(attempt+1);}}><Text style={styles.retryText}>Reconnect</Text></Pressable>
  </View> : <WebView key={attempt} ref={web} source={{uri}} style={{flex:1,backgroundColor:background}}
   originWhitelist={[new URL(uri).origin]} onShouldStartLoadWithRequest={request=>allowsNavigation(request.url,uri)}
   onLoadStart={()=>incoming.current.setReady(false)} onMessage={onMessage} onError={event=>setError(event.nativeEvent.description)} onHttpError={event=>setError(`Could not open the reader (${event.nativeEvent.statusCode}).`)}
   startInLoadingState renderLoading={()=> <View style={[styles.loading,{backgroundColor:background}]}><ActivityIndicator size="large" color="#438ee3"/><Text style={[styles.description,{color:ink}]}>Preparing your workspace…</Text></View>}
   allowsInlineMediaPlayback mediaPlaybackRequiresUserAction bounces={false} allowsBackForwardNavigationGestures={false}
   setSupportMultipleWindows={false} javaScriptEnabled domStorageEnabled textZoom={100}
  />}
 </SafeAreaView></SafeAreaProvider>;
}
const styles = StyleSheet.create({
 root:{flex:1}, loading:{...StyleSheet.absoluteFillObject,alignItems:'center',justifyContent:'center',gap:20},
 message:{flex:1,justifyContent:'center',padding:32,gap:20}, title:{fontSize:30,fontWeight:'600',letterSpacing:-1},
 description:{fontSize:16,lineHeight:25,opacity:.8},detail:{fontSize:12,lineHeight:18,opacity:.65},
 retry:{alignSelf:'flex-start',paddingHorizontal:24,paddingVertical:14,backgroundColor:'#1765ce',borderRadius:16},retryText:{color:'white',fontSize:16,fontWeight:'600'},
});
